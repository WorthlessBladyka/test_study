FROM python:3.10-slim AS builder

WORKDIR /builder

COPY app /builder/app
COPY app/*.py /builder/app/
COPY installapp.txt .
COPY cmd.sh .


RUN apt-get update && \
    apt-get install -y gcc build-essential && \
    rm -rf /var/lib/apt/lists/* && \
    pip install --no-cache-dir -r installapp.txt

# Проверка
RUN pip show Flask
RUN pip show Jinja2
RUN pip show uwsgi
RUN ls -la /usr/local/bin/
RUN ls -la /usr/local/lib/python3.10/site-packages/

FROM python:3.10-slim

WORKDIR /app

COPY --from=builder /builder/app ./app
COPY --from=builder /builder/app/*.py ./app/
COPY --from=builder /builder/cmd.sh .
COPY --from=builder /usr/local/bin /usr/local/bin
COPY --from=builder /usr/local/lib/python3.10/site-packages /usr/local/lib/python3.10/site-packages/

# Проверка
RUN pip show Flask
RUN pip show Jinja2
RUN pip show uwsgi
RUN ls -la /usr/local/bin/
RUN ls -la /usr/local/lib/python3.10/site-packages/

RUN groupadd -r uwsgi && \
    useradd -r -g uwsgi uwsgi && \
    chmod +x cmd.sh && \
    chown -R uwsgi:uwsgi /app && \
    mkdir -p /usr/local/lib/python3.10/site-packages && \
    mkdir -p /usr/local/bin

EXPOSE 9090 9191

USER uwsgi

CMD [ "./cmd.sh" ]
