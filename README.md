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
        'http://example.com/server.php',
        [
            'secret' => 'a secret password'
        ]
    );
    
    // or by function
    $client = plinker_client('http://example.com/server.php', 'a secret password');

    echo '<pre>'.print_r($client->testclass->foobar(), true).'</pre>';


** The server.php listener **

    <?php
    /**
     * Its Plinker!
     */
    if (isset($_SERVER['HTTP_PLINKER'])) {
        // init plinker server
        (new \Plinker\Server([
            'secret' => 'a secret password',
            'allowed_ips' => [
                '127.0.0.1'
            ],
            'classes' => [
                'test' => [
                    // path to file
                    'classes/test.php',
                    // addtional key/values
                    [
                        'key' => 'value'
                    ]
                ],
                // ...
            ]
        ]))->listen();
    }
    
    //or by function
    <?php
    /**
     * Its Plinker!
     */
    if (isset($_SERVER['HTTP_PLINKER'])) {
        // init plinker server
        plinker_server([
            'secret' => '12sdecf5',
            'allowed_ips' => [
                '127.0.0.1'
            ],
            'classes' => [
                'test' => [
                    // path to file
                    'classes/test.php',
                    // addtional key/values
                    [
                        'key' => 'value'
                    ]
                ],
                // ...
            ]
        ]);
    }


See the [organisations page](https://github.com/plinker-rpc) for additional components.