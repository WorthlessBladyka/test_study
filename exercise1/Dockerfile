#1 Building dependencies
FROM python:3.10-slim AS building

WORKDIR /building

COPY installapp.txt .

RUN apt-get update && apt-get install -y gcc build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    pip install --no-cache-dir -r installapp.txt


#2 Building app
FROM python:3.10-slim

WORKDIR /app

COPY app /app/app
COPY app/*.py /app/app

COPY cmd.sh .
COPY --from=building /usr/local/bin /usr/local/bin/
COPY --from=building /usr/local/lib/python3.10/site-packages /usr/local/lib/python3.10/site-packages

RUN groupadd -r uwsgi && useradd -r -g uwsgi uwsgi && \
    chown -R uwsgi:uwsgi /app && \
    chmod +x ./cmd.sh 

USER uwsgi

EXPOSE 9090 9191

CMD ["/bin/bash", "/app/cmd.sh"]