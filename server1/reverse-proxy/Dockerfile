FROM alpine:3.23.3

USER root

RUN apk update && \
apk add nginx && \
mkdir -m 755 /etc/nginx/sites-avalible/ /etc/nginx/sites-enabled/ && \
chown -R nginx:nginx /run/nginx/

COPY ./nginx /etc/nginx/
COPY ./nginx/sites-avalible /etc/nginx/sites-avalible

RUN ln -sf /etc/nginx/sites-avalible/proxy.conf /etc/nginx/sites-enabled/

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]