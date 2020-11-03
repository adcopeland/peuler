# Docker (linux or WSL2)
First, build the docker runner: `docker build -t peuler .`

Then run: `docker run -it --rm -v $(pwd):/src -w /src peuler make LANGUAGE=cpp PROBLEM=1

Where LANGUAGE can be cpp, rust, golang and PROBLEM can be anything output by `bash list.sh <LANGUAGE>`

# Non-docker
Need bash and make plus whatever is needed for the language (rust, cargo, golang, g++)

Then, directly run `make LANGUAGE=<LANGUAGE> PROBLEM=<PROBLEM>` or `bash run.sh <LANGUAGE> <PROBLEM>` outside of docker
