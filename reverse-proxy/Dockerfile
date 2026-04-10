FROM alpine:3.23.3

USER root

RUN apk update && \
apk add nginx && \
mkdir -m 755 /etc/nginx/sites-avalibles/ /etc/nginx/sites-enabled/ && \
chown -R nginx:nginx /run/nginx/

COPY ./nginx /etc/nginx/
COPY ./nginx/sites-avalibles /etc/nginx/sites-avalibles

RUN ln -sf /etc/nginx/sites-avalibles/proxy.conf /etc/nginx/sites-enabled/

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]