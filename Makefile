
ifeq ($(shell whoami),root)
	NPM_OPTS=--unsafe-perm
else
	NPM_OPTS=
endif

.PHONY: all
all:
	npm install $(NPM_OPTS)

.PHONY: clean
clean:
	rm -rf build node_modules npm-debug.log

.PHONY: test
test:
	echo ""
	-node -e "console.log(require('./').zone_get_state('one', 'two'))"
	echo ""
	-node -e "console.log(require('./').zone_get_state('$(shell zonename)'))"
	echo ""
	-node -e "console.log(require('./').zone_get_state('bogus'))"
