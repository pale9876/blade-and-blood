FROM rust:latest as builder

WORKDIR /app

COPY Cargo.toml Cargo.lock ./

COPY src ./src

RUN cargo fetch

RUN cargo build --release

FROM ubuntu:latest

WORKDIR /app

COPY --from=builder /app/target/release/bnb-server /app/bnb-server

EXPOSE 3000

CMD [ "/app/bnb-server" ]