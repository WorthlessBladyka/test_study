FROM python:3.10-slim

WORKDIR /app

COPY app /app
COPY app/identidock.py .
COPY installapp.txt .
COPY cmd.sh .

RUN apt-get update && apt-get install -y \
    gcc \
    build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    groupadd -r uwsgi && useradd -r -g uwsgi uwsgi && \
    chmod +x ./cmd.sh && \
    chown -R uwsgi:uwsgi /app

RUN pip install --no-cache-dir -r installapp.txt

USER uwsgi

EXPOSE 9090 9191

CMD ["/bin/bash", "/app/cmd.sh"]