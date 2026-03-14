FROM nginx:1.29.5-trixie-perl

COPY WEB /usr/share/nginx/html

RUN mkdir -p /etc/nginx/sites-available && \
    mkdir -p /etc/nginx/sites-enabled

COPY nginx.conf /etc/nginx/nginx.conf
COPY sites-available/ /etc/nginx/sites-available

RUN ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default
RUN ln -s /etc/nginx/sites-available/site1 /etc/nginx/sites-enabled/site1
RUN ln -s /etc/nginx/sites-available/site2 /etc/nginx/sites-enabled/site2

<<<<<<< HEAD:Dockerfile
EXPOSE 80
=======
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
>>>>>>> dcdaba6 (multibuilding + optimization layers):exercise1/Dockerfile
