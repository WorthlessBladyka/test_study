FROM python:3.10-slim AS builder

WORKDIR /builder

COPY installapp.txt .

RUN apt-get update && \
    apt-get install -y gcc build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    pip install --no-cache-dir -r installapp.txt

FROM python:3.10-slim

WORKDIR /app

COPY app /app
COPY app/identidock.py .
COPY installapp.txt .
COPY cmd.sh .

RUN groupadd -r uwsgi && \
    useradd -r -g uwsgi uwsgi && \
    chmod +x cmd.sh && \
    chown -R uwsgi:uwsgi /app && \
    mkdir -p /usr/local/lib/python3.10/site-packages && \
    mkdir -p /usr/local/bin

COPY --from=builder /usr/local/lib/python3.10/site-packages/* /usr/local/lib/python3.10/site-packages
COPY --from=builder /usr/local/bin/* /usr/local/bin

EXPOSE 9090 9191

USER uwsgi

CMD [ "./cmd.sh" ]
