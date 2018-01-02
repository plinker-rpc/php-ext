/*
 +------------------------------------------------------------------------+
 | PHP LXD Extension                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c)2017-2017 LXC.systems (https://github.com/lxc-systems/lxd)|
 +------------------------------------------------------------------------+
 | This source file is subject to GNU General Public License v2.0 License |
 | that is bundled with this package in the file LICENSE.                 |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@lxd.systems so we can send you a copy immediately.          |
 +------------------------------------------------------------------------+
 | Authors: Lawrence Cherone <lawrence@lxd.systems>                       |
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

    private endpoint;
    private component;
    private publicKey;
    private privateKey;
    private encrypt;
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
    public function __get(string! method)
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
    public function __call(string! action, array! params)
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
        
        /*
        // check response is a serialized string
        if (@unserialize(this->response->body) === false) {
            throw new \Exception("Could not unserialize response: ".$this->response->body);
        }

        // initial unserialize response body
        $this->response->body = unserialize($this->response->body);

        // decode response
        $this->response->data = $this->signer->decode(
            $this->response->body
        );

        // verify response packet timing validity
        $this->response->data["packet_time"] = microtime(true) - $this->response->body["time"];
        if ($this->response->data["packet_time"] >= 1) {
            throw new \Exception("Response timing packet check failed");
        }

        // verify data timing validity
        $this->response->data["data_time"] = (microtime(true) - $this->response->data["time"]);
        if ($this->response->data["data_time"] >= 1) {
            throw new \Exception("Response timing data check failed");
        }

        // decode response data
        if (is_string($this->response->data["response"])) {
            // empty data response
            if (empty($this->response->data["response"])) {
                return "";
            }
            // response should be a serialized string
            if (@unserialize($this->response->data["response"]) === false) {
                throw new \Exception("Could not unserialize response: ".$this->response->data["response"]);
            }
            $this->response->data["response"] = unserialize($this->response->data["response"]);
        }

        // check for errors
        if (is_array($this->response->data["response"]) && !empty($this->response->data["response"]["error"])) {
            throw new \Exception(ucfirst($this->response->data["response"]["error"]));
        }
        */

        // unserialize data
        return unserialize(this->response);
    }

}
