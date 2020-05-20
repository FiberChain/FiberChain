FROM ubuntu:16.04
# Build dependencies
RUN /bin/bash -c 'apt-get update'
RUN /bin/bash -c 'apt-get install -y \
    autoconf \
    automake \
    cmake \
    g++ \
    git \
    libbz2-dev \
    libsnappy-dev \
    libssl-dev \
    libtool \
    make \
    pkg-config \
    python3 \
    python3-jinja2 \
    doxygen \
    libboost-chrono-dev \
    libboost-context-dev \
    libboost-coroutine-dev \
    libboost-date-time-dev \
    libboost-filesystem-dev \
    libboost-iostreams-dev \
    libboost-locale-dev \
    libboost-program-options-dev \
    libboost-serialization-dev \
    libboost-signals-dev \
    libboost-system-dev \
    libboost-test-dev \
    libboost-thread-dev \
    libncurses5-dev \
    libreadline-dev \
    perl'

ARG BUILD_CONF
ENV BUILD_CONF ${BUILD_CONF:-Release}

RUN mkdir /var/program

ENTRYPOINT ["/bin/bash", "-c", "cd /var/program && ./build.sh"]
