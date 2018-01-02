## Plinker RPC - PHP extension!

Plinker PHP RPC client/server makes it really easy to link and execute PHP component classes on remote systems, while maintaining the feel of a local method call.

Some difference between this and the composer lib version, main one is its delivered as a PHP extension!

Other changes include:

 - Built-in and User defined components, so only one client instance is needed
 - Encryption always


Making a remote call.
--------------------


    <?php
    $client = new \Plinker\Client(
        'http://127.0.0.1:81/server.php',
        [
            'secret' => 'a secret password, if set all clients should use the same secret'
        ]
    );
    echo '<pre>'.print_r($client->testclass->foobar(), true).'</pre>';


**then the server.php part...**

    <?php
    /**
     * Its Plinker!
     */
    if (isset($_SERVER['HTTP_PLINKER'])) {
        //
        (new \Plinker\Server([
            'secret' => 'a secret password, if set all clients should use the same secret',
            'allowed_ips' => [
                '127.0.0.1'
            ],
            // user defined class map, key is the property e.g $client->testclass->foobar();
            'classes' => [
                'testclass' => '/path/to/testclass.php'
            ]
        ]))->listen();
    }

See the [organisations page](https://github.com/plinker-rpc) for additional components.