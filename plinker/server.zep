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

use Plinker\Lib\Signer;

final class Server
{
    protected post;
    protected signer;
    protected config;

    /**
     *
     */
    public function __construct(array! config = []) -> void
    {
        let this->config = array_merge([
            "secret"      : null,
            "allowed_ips" : [],
            "endpoint"    : null
        ], config);

        // check and set client timeout
        if !isset this->config["timeout"] || !is_numeric(this->config["timeout"]) {
            let this->config["timeout"] = 10;
        }
    }

    /**
     *
     */
    public function listen() -> void
    {
        let this->post = file_get_contents("php://input");
        let this->post = json_decode(this->post, true);

        header("Content-Type: text/plain; charset=utf-8");

        // check allowed ips
        if !empty this->config["allowed_ips"] &&
           !in_array(_SERVER["REMOTE_ADDR"], this->config["allowed_ips"]) {
            exit(serialize([
                "error" : "IP not in allowed list ("._SERVER["REMOTE_ADDR"].")",
                "code" : 403
            ]));
        }
        
        // check header token matches data token
        if _SERVER["HTTP_PLINKER"] != this->post["token"] {
            exit(serialize([
                "error" : "Plinker token mismatch",
                "code" : 422
            ]));
        }

        // load signer
        if !<Plinker\Lib\Signer> (this->signer) {
            let this->signer = new Signer(this->config);
        }

        // decode post payload
        let this->post = this->signer->decode(this->post);

        // could not decode payload
        if this->post === null {
            exit(serialize([
                "error" : "Failed to decode payload, check secret",
                "code" : 422
            ]));
        }

        //
        var ns;
        var action = this->post["action"];
        var response;

        // component is in classes config
        if array_key_exists(this->post["component"], this->config["classes"]) {
            //
            let ns = this->config["classes"][this->post["component"]];
            
            //
            if !file_exists(ns) {
                exit(serialize([
                    "error" : "Component class not found",
                    "code"  : 422
                ]));
            }
            
            // load and eval class (include, require not supported)
            var src = file_get_contents(ns);
            eval("?>" . src);

            //
            if !class_exists(this->post["component"]) {
                exit(serialize([
                    "error" : "Component class name invalid",
                    "code"  : 422
                ]));
            }
            
            //
            let response = this->execute(this->post["component"], action);

            exit(serialize(response));
        }

        // component is plinker endpoint
        let ns = "\\Plinker\\Endpoint\\".this->post["component"];
        
        if class_exists(ns) {
            //
            let response = this->execute(ns, action);
        } else {
            let response = "Component not implemented";
        }

        exit(serialize(response));
    }
    
    /**
     *
     */
    private function execute(ns, action) -> string
    {
        var response  = null, component;
        let component = new {ns}(this->config+this->post);

        if method_exists(component, action) {
            let response = call_user_func_array(
                [
                    component,
                    action
                ],
                this->post["params"]
            );
        } else {
            let response = "Component action (".action.") not implemented in: ".ns;
        }
        
        return response;
    }

}
