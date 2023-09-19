# HTTP Server

The task is to program a  create a simple asynchronous HTTP server with configuration loading and logging.

The user can start the server from the command line by specifying a configuration file.
for example: ./Server config.cfg

The server implements:

- loading the configuration file
- network listening parameters (IP address, port)
- restrictions on working with a specific directory
- transmission log (where it should be saved, in what format, how the header of each record should look, ...)
- turning off the server at the (configurable) URL address

An HTTP server can serve multiple domains or provide a virtual file system (mapping virtual URLs to physical paths on the disk)

## Config file structure

White characters in the configuration file are ignored
The configuration file consists of pairs of the form
"key=value;"

Supported settings:
- logfile) value should be the path to the file where the logs will be stored
If not specified, logs will be written to the console
- listen) value should be the ip and port of listening to the network
If not specified, defaults to "0.0.0.0:8080"
- virtualfs) value must be a comma-separated list of url=content pairs in braces
these pairs define the mapping of virtual URLs to content generators

## Supported content generators
- File) file:path - allows you to display the contents of the file
- Directory) dir:path - allows you to display the contents of the folder
- Script) script:path - allows you to get the result of running a script or program
supports queries in url, for example, url?a&b&c means call script with arguments a b c
- Vypinac) special:terminator - allows you to set the address in the configuration (plus more addresses) at which the server will be shut down

The server redirects the request to the content generator according to the longest match of the beginning of the URL address

## Login
The server stores logs in the Common Log Format and supports writing them to a file or console.
Each line describes one served HTTP request. The line format is:
```client ident user [date] "request" status length```

## Where do I have polymorphism?
The abstract class `Actor` has a virtual method `Run` which is overloaded in descendants
This method is responsible for performing actions by the actor in case of an IO event. For example, the `Receiver` class reads data from the socket non-blockingly by calling this method until it is exhausted, the `Accepter` accepts new clients, and the `Queuer` processes messages
`Run` is called in the `Start` method of the `HTTPServer` class, which in a cycle receives from epoll the next actor with which some event happened and calls its method

The abstract class `Queuer` representing the actor that sequentially processes the message queue has a virtual `Handle` method, overloaded variants that actually define the response to each message in the child classes.
For example, the `Logger` class processes the recording of the received log into the corresponding stream, while the content generator classes receive HTTP requests and implement the logic of processing these requests in the `Handle` method

Additionally, the `Queuer` class implements parametric polymorphism specifically in that the message type is specified by a template.
For example `Sender` and `Logger` work with strings and `ContentGenerator` with `HTTPRequest`

## Examples
The examples directory contains an example configuration file: server.cfg and 2 scripts: sum.sh and factorial.sh for demonstration.

Сonfig configures the server so that
- listened to address 0.0.0.0 on port 8080,
- wrote logs to the file examples/server.log,
- displayed at http://127.0.0.1:8080 address book doc/ with project documentation,
- at http://127.0.0.1:8080/sum there is a script call that adds two numbers,
- at the address http://127.0.0.1:8080/factorial there is a call to a script that calculates the factorial of a given number,
- at the address http://127.0.0.1:8080/exit the server shuts down
