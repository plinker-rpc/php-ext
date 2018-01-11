/*
 +------------------------------------------------------------------------+
 | Plinker PHP Extension                                                  |
 +------------------------------------------------------------------------+
 | Copyright (c)2017-2017 (https://github.com/plinker-rpc/php-ext)        |
 +------------------------------------------------------------------------+
 | This source file is subject to GNU General Public License v2.0 License |
 | that is bundled with this package in the file LICENSE.                 |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@cherone.co.uk so we can send you a copy immediately.        |
 +------------------------------------------------------------------------+
 | Authors: Lawrence Cherone <lawrence@cherone.co.uk>                     |
 +------------------------------------------------------------------------+
 */

// global connect function
/*
function lxd_connect(string! url, string! secret, array! options = []) {
    return (new \Lxd\Client(options))->connect(url, secret);
}
*/

namespace Plinker;

use Plinker\Lib\Curl;
use Plinker\Lib\Signer;

final class Client
{
    private component;
    private response;

    protected config;
    protected curl;
    protected signer;

    /**
     *
     */
    public function __construct(string! server, array config = []) -> void
    {
        let this->config = array_merge([
            "server" : server,
            "secret" : null
        ], config);

        // check and set client timeout
        if !isset this->config["timeout"] || !is_numeric(this->config["timeout"]) {
            let this->config["timeout"] = 10;
        }
    }

    /**
     *
     */
    public function __get(string! method) -> <Plinker\Client>
    {
        let this->component = method;

        return this;
    }

    /**
     * Magic caller
     *
     * @param string $action
     * @param array  $params
     */
    public function __call(string! action, array! params) -> string
    {
        if !is_scalar(action) {
            throw new \Exception("Method name has no scalar value");
        }
        
        if !is_array(params) {
            throw new \Exception("Params must be given as array");
        }
        
        // load curl
        if !<Plinker\Lib\Curl> (this->curl) {
            let this->curl = new Curl(this->config);
        }  
        
        // load signer
        if !<Plinker\Lib\Signer> (this->signer) {
            let this->signer = new Signer(this->config);
        }

        // change params array into numeric
        let params = array_values(params);

        // unset local private key
        //unset(this->config["plinker"]["private_key"]);

        var payload = this->signer->encode([
            "component" : this->component,
            "config" : this->config,
            "action" : action,
            "params" : params
        ]);

        let this->response = this->curl->post(this->config["server"], payload, [
            "PLINKER: ".payload["token"]
        ]);

        // unserialize data
        return unserialize(this->response);
    }

}
