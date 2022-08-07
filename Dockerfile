########################################################################
# Build/Dev Image
########################################################################
FROM ubuntu:20.04 AS dev-build

# Set application dir
ENV APPLICATION_DIR=/app

# Set timezone
ENV TZ=Asia/Kolkata
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Installing dependencies
# RUN apt-get update

# Install formatter
RUN apt-get update && apt-get install -y clang-format

RUN apt-get install -y \
  # For vcpkg
  git curl zip \
  # For packages
  cmake g++ pkg-config autoconf


# Install dependency manager (vcpkg)
RUN git clone https://github.com/Microsoft/vcpkg.git

WORKDIR /vcpkg
RUN ./bootstrap-vcpkg.sh -disableMetrics

# Installing packages
RUN ./vcpkg install oatpp
RUN ./vcpkg install oatpp-postgresql
RUN ./vcpkg install oatpp-swagger
RUN ./vcpkg install openssl

RUN mkdir /root/.vcpkg && touch /root/.vcpkg/vcpkg.path.txt && ./vcpkg integrate install

# # Create appuser.
# ENV USER=appuser
# ENV UID=10001
# # See https://stackoverflow.com/a/55757473/12429735RUN
# RUN adduser \
#   --disabled-password \
#   --gecos "" \
#   --home "/nonexistent" \
#   --shell "/sbin/nologin" \
#   --no-create-home \
#   --uid "${UID}" \
#   "${USER}"

# Copy source
COPY . ${APPLICATION_DIR}

# Add APPLICATION_DIR to git safe.directory
RUN git config --global --add safe.directory ${APPLICATION_DIR}

# Compile
RUN mkdir build

WORKDIR ${APPLICATION_DIR}/build

RUN cmake ..
RUN make

########################################################################
# Production Image
########################################################################
FROM scratch AS production

# # Import the user and group files from the dev-build.
# COPY --from=dev-build /etc/passwd /etc/passwd
# COPY --from=dev-build /etc/group /etc/group

# Import certs from the dev-build
COPY --from=dev-build /etc/ssl/certs/ca-certificates.crt /etc/ssl/certs/

# Import timezone from the dev-build
COPY --from=dev-build /usr/share/zoneinfo /usr/share/zoneinfo

# Import application from the dev-build
COPY --from=dev-build /app/build/todo-exe /

# Use an unprivileged user.
USER appuser:appuser

EXPOSE 8000

ENTRYPOINT [ "./todo-exe" ]