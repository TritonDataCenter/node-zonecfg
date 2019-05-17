
TAP_EXEC = ./node_modules/.bin/tap
TEST_JOBS ?= 10
TEST_TIMEOUT_S ?= 1200
TEST_GLOB ?= *

# If running as root, 'npm install' will not run scripts, even the default
# 'install' script that runs node-gyp to build with binding.gyp.
# '--unsafe-perm' works around that.
ifeq ($(shell whoami),root)
	NPM_OPTS=--unsafe-perm
else
	NPM_OPTS=
endif

.PHONY: all
all $(TAP_EXEC):
	npm install $(NPM_OPTS)

.PHONY: clean
clean:
	rm -rf build node_modules npm-debug.log zonecfg-*.tgz

.PHONY: test
test: $(TAP_EXEC)
	$(TAP_EXEC) --timeout $(TEST_TIMEOUT_S) -j $(TEST_JOBS) \
		-o ./test.tap test/$(TEST_GLOB).test.js

.PHONY: play
play:
	echo ""
	-node -e "console.log(require('./').zone_get_state('$(shell zonename)'))"
	echo ""
	-node -e "console.log(require('./').zone_get_state('bogus'))"
