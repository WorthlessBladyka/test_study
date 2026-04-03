FROM jenkins/jenkins:2.556

USER root

RUN apt update && \
apt install -y docker.io docker-compose docker-doc && \
groupdel docker && groupadd -g 995 docker && \
usermod -aG docker jenkins

USER jenkins
