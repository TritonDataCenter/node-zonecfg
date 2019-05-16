This is a binary Node.js binding to a small subset of libzonecfg on
illumos/SmartOS. It uses N-API, which IIUC was added to node in v6.
Currently testing is done against node v6.


# Install / Build

    npm install

Note: If you are running as root you will see this warning
(see [npm/npm#3497](https://github.com/npm/npm/issues/3497)):

    npm WARN lifecycle zonecfg@1.0.0~install: cannot run in wd zonecfg@1.0.0 node-gyp rebuild (wd=...)

You then need to use:

    npm install --unsafe-perm


# Usage

TODO


# Reference

## Raw API

These are APIs that attempt to match as closely as possible to the raw
libzonecfg APIs. See:

- https://github.com/joyent/illumos-joyent/blob/master/usr/src/head/libzonecfg.h
- https://github.com/joyent/illumos-joyent/blob/master/usr/src/lib/libzonecfg/common/libzonecfg.c

### `zone_get_state(zone_name)`

Returns the `zone_state_t` (an integer) state of the given zone.
Throws an `Error` on any failure.
Use `zone_state_str()` to convert that to the zone state string like "running".
See convenience method `zone_get_state_str`.

Parameters:
- `zone_name` - String zone name. Typically on SmartOS this is 'global' or a
  UUID.

### `zone_state_str(zone_state_t)`

Converts a `zone_state_t` (an integer), as from `zone_get_state`, to a zone state string
like "running" or "configured".

Parameters:
- `zone_state_t` - Integer, typically from `zone_get_state`.


## Convenience API

These are APIs that wrap one or more raw libzonecfg APIs to provide something
typically more convenient for Node.js usage. Opinions on usefulness may vary.

### `zone_get_state_str(zone_name)`

Gets the zone state string (e.g. "running", "configured") for the given
`zone_name` string.  Throws an `Error` on any failure.

Parameters:
- `zone_name` - String zone name. Typically on SmartOS this is 'global' or a
  UUID.


## See Also

- [node-zutil](https://github.com/joyent/node-zutil) has bindings for some
  of libzonecfg and libzone (?, at least for /usr/include/zone.h) on
  illumos/SmartOS. However, it uses waf and supports node 0.6 and node 0.8
  only (with a patch floating around in orlandov/node-zutil for node 0.10
  support).
