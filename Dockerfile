FROM alpine:3.19.1 as build
RUN apk update && apk add --no-cache \
	build-base \
	cmake \
	git
WORKDIR /app
COPY CMakeLists.txt .
COPY rpncalc.cxx .
COPY rpn.hxx .
COPY vendor ./vendor
COPY test ./test
RUN ls -l
RUN ls -l vendor
RUN cmake -B build -S . && cmake --build build && ctest --test-dir build test_eval

FROM alpine:3.19.1
RUN apk update && apk add --no-cache \
	libstdc++
COPY --from=build ./app/build/rpncalc ./app/
ENTRYPOINT ["./app/rpncalc"]
