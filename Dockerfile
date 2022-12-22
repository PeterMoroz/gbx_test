FROM debian:11

RUN apt-get update && \
	apt-get install -y \
	build-essential \
	g++ \
	cmake \
	libgtest-dev	
