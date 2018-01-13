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
function plinker_server(array! options = []) {
    (new \Plinker\Server(options))->listen();
}

namespace Plinker;

use Plinker\Lib\Signer;

final class Server
{
    /**
     * @var
     */
    protected post;
    
    /**
     * @var
     */
    protected config;
    
    /**
     * @var
     */
    protected signer;
    
    /**
     * @const - error strings
     */
    const ERROR_IP    = "IP not in allowed list (%s)";
    const ERROR_TOKEN = "Plinker token mismatch";
    const ERROR_DECODE = "Failed to decode payload, check secret";
    const ERROR_USR_COMPONENT = "User component class (%s) not found";
    const ERROR_EXT_COMPONENT = "Component (%s) not implemented";
    const ERROR_ACTION = "Component action (%s) not implemented in: %s";

    /**
     * Class construct
     *
     * @param  array          config config array which holds object configuration
     * @return void
     */
    public function __construct(array! config = []) -> void
    {
        let this->config = array_merge([
            "debug"       : false,
            "secret"      : null,
            "allowed_ips" : []
        ], config);

        // check and set client timeout
        if !isset this->config["timeout"] || !is_numeric(this->config["timeout"]) {
            let this->config["timeout"] = 10;
        }
    }

    /**
     * Listen method
     *
     * <code>
     *  $server->listen();
     * </code>
     *
     * @return void
     */
    public function listen() -> void
    {
        let this->post = file_get_contents("php://input");
        let this->post = gzinflate(this->post);
        let this->post = json_decode(this->post, true);

        header("Content-Type: text/plain; charset=utf-8");

        // check allowed ips
        if !empty this->config["allowed_ips"] &&
           !in_array(_SERVER["REMOTE_ADDR"], this->config["allowed_ips"]) {
            exit(serialize([
                "error" : sprintf(Server::ERROR_IP, _SERVER["REMOTE_ADDR"]),
                "code" : 403
            ]));
        }
        
        // check header token matches data token
        if _SERVER["HTTP_PLINKER"] != this->post["token"] {
            exit(serialize([
                "error" : Server::ERROR_TOKEN,
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
                "error" : Server::ERROR_DECODE,
                "code" : 422
            ]));
        }
        
        //
        var response, ns, action = this->post["action"];
        let this->config = array_merge(
            this->config, 
            this->post
        );
        
        // component is in classes config
        if array_key_exists(this->post["component"], this->config["classes"]) {
            //
            if !empty this->config["classes"][this->post["component"]][0] {
                let ns = this->config["classes"][this->post["component"]][0];
            }
            
            //
            if !empty this->config["classes"][this->post["component"]][1] {
                let this->config = array_merge(
                    this->config, 
                    this->config["classes"][this->post["component"]][1]
                );
            }
            
            //
            if !empty ns && !file_exists(ns) {
                exit(serialize([
                    "error" : sprintf(Server::ERROR_USR_COMPONENT, this->post["component"]),
                    "code"  : 422
                ]));
            }
            
            //
            require(ns);

            //
            if !class_exists(this->post["component"]) {
                exit(serialize([
                    "error" : sprintf(Server::ERROR_USR_COMPONENT, this->post["component"]),
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
            if empty this->post["component"] && action === "info" {
                let response = this->info();
            } else {
                let response = sprintf(Server::ERROR_EXT_COMPONENT, this->post["component"]);
            }
        }

        exit(serialize(response));
    }
    
    /**
     * Return info about available classes
     *
     * <code>
     *  $client->info();
     * </code>
     *
     * @return array
     */
    private function info() -> array
    {
        var response = [
                "class" : []
            ], 
            reflection, 
            key, 
            val, 
            method, 
            parameter, 
            param = [];
        
        for key, val in this->config["classes"] {
            //
            require(val[0]);
            
            let reflection = new \ReflectionClass(key);

            for method in reflection->getMethods() {
                if !in_array(method->getName(), ["__construct"]) {
                    let param = [];
                    for parameter in method->getParameters() {
                        let param[] = parameter->getName();
                    }
                    let response["class"][key]["methods"][method->getName()] = param;
                }
            }
        }
        
        return response;
    }
    
    /**
     * Execute component
     *
     * @param  ns      component class namespace
     * @param  action  component action
     * @return string
     */
    private function execute(ns, action) -> string
    {
        var response  = null, component;
        let component = new {ns}(this->config);

        if method_exists(component, action) {
            let response = call_user_func_array(
                [
                    component,
                    action
                ],
                this->post["params"]
            );
        } else {
            let response = sprintf(Server::ERROR_ACTION, action, ns);
        }
        
        return response;
    }

}
