from fastapi import FastAPI, Form, Request
from fastapi.responses import HTMLResponse, Response
import hashlib
import httpx
from redis.asyncio import Redis

app = FastAPI()

# Подключение к Redis (асинхронное)
cache = Redis(host='redis', port=6379, db=0, decode_responses=False)

salt = "UNIQUE_SALT"
default_name = 'Joe Bloggs'

@app.api_route("/api/", methods=["GET", "POST"])
async def mainpage(request: Request, name: str = Form(default=default_name)):
    """
    Обрабатывает GET (показать форму) и POST (принять имя, показать форму + картинку).
    """
    name_hash = None

    if request.method == "POST":
        salted_name = salt + name
        name_hash = hashlib.sha256(salted_name.encode()).hexdigest()

    # Формируем HTML
    html_header = '<html><head><title>Identidock</title></head><body>'
    
    if name_hash:
        html_body = f'''<form method="POST">
        Hello <input type="text" name="name" value="{name}">
        <input type="submit" value="submit">
        </form>
        <p>You look like a:
        <img src="/api/monster/{name_hash}"/>
        '''
    else:
        html_body = f'''<form method="POST">
        Hello <input type="text" name="name" value="{name}">
        <input type="submit" value="submit">
        </form>
        '''
    
    html_footer = '</body></html>'
    return HTMLResponse(content=html_header + html_body + html_footer)

@app.get("/api/monster/{name}")
async def get_identicon(name: str):
    """
    Возвращает изображение-идентикон. Сначала проверяет Redis,
    при промахе обращается к внешнему сервису (http://192.168.1.60:8080/monster/...)
    и сохраняет результат в Redis.
    """
    # Пытаемся получить изображение из кэша
    image = await cache.get(name)
    
    if image is None:
        print("Cache miss (промах кэша)", flush=True)
        # Формируем правильный URL (в оригинале был пропущен /monster/)
        url = f"http://192.168.1.60:8080/monster/{name}?size=80"
        async with httpx.AsyncClient() as client:
            resp = await client.get(url)
            image = resp.content
        # Сохраняем в Redis
        await cache.set(name, image)
    
    return Response(content=image, media_type="image/png")

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=9090)