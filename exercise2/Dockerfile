FROM jenkins/jenkins:latest

USER root

RUN apt update && \
apt install docker.io docker-compose docker-doc && \
groupadd -g 995 docker && \
chmod -aG docker jenkins

USER jenkins