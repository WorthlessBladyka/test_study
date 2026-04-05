from fastapi import FastAPI

app = FastAPI()

@app.get("/hotels/{hotels_id}")
def get_hotels(hotels_id: str):
	return "Отель " + hotels_id