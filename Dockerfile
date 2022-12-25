FROM debian:11

ARG CACHEBUST=1

RUN apt-get update && \
	apt-get install -y \
	build-essential \
	g++ \
	cmake \
	git \
	python3 \
	python3-pip \
	postgresql \
	postgresql-contrib
	
RUN pip3 install conan
RUN pg_ctlcluster 13 main start && su -c "psql -c \"ALTER USER postgres PASSWORD 'pguser';\"" postgres && su -c "createdb -U postgres gbx" postgres
