FROM nginx:1.29.5-trixie-perl

COPY WEB /usr/share/nginx/html

RUN mkdir -p /etc/nginx/sites-available && \
    mkdir -p /etc/nginx/sites-enabled

COPY nginx.conf /etc/nginx/nginx.conf
COPY sites-available/ /etc/nginx/sites-available

RUN ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default
RUN ln -s /etc/nginx/sites-available/site1 /etc/nginx/sites-enabled/site1
RUN ln -s /etc/nginx/sites-available/site2 /etc/nginx/sites-enabled/site2

EXPOSE 80