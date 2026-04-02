FROM jenkins/jenkins:2.556

USER root

RUN apt update
RUN apt install -y docker.io docker-compose docker-doc
RUN groupdel docker && groupadd -g 995 docker
RUN usermod -aG docker jenkins

USER jenkins