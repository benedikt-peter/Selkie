FROM ubuntu:24.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y build-essential \
      gcc \
      g++ \
      ninja-build \
      cmake \
      locales-all \
  && apt-get clean