FROM debian:latest
ENV debian_frontend=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      ninja-build \
      pkg-config \
      git \
      ca-certificates \
      curl \
      unzip \
      tar \
      python3 \
      && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

WORKDIR /app/build

RUN cmake ..  && \
    make

CMD ["/app/build/inz"]