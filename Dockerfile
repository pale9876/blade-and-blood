FROM rust:1.84.1-bullseye as builder
WORKDIR /app
COPY Cargo.toml Cargo.lock ./
COPY src ./src
RUN cargo fetch
RUN cargo build --release
#stage 2
FROM debian:bullseye-slim
WORKDIR /app
COPY --from=builder /app/target/release/blade-and-blood /app/blade-and-blood
EXPOSE 3000
CMD [ "/app/blade-and-blood" ]