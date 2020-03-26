FROM ubuntu:18.04

ADD ./out /var/program/fiberchain

ENTRYPOINT /var/program/fiberchain/futurepiad
