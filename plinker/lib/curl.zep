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

namespace Plinker\Lib;

final class Curl
{
    private config;
    private options;

    /**
     *
     */
    public function __construct(array! config = []) -> void
    {
        //
        let this->config = config;
    }

    final private function setOptions() -> void
    {
        //
        let this->options = [
            CURLOPT_FAILONERROR    : true,
            CURLOPT_FOLLOWLOCATION : true,
            CURLOPT_RETURNTRANSFER : true,
            CURLOPT_SSL_VERIFYPEER : false,
            CURLOPT_SSL_VERIFYHOST : false,
            CURLOPT_HTTPHEADER     : [
                "Content-Type: application/json"
            ]
        ];
    } 

    /**
     *  GET
     *  Should handle non json response
     */
    public function get(string! url, array! parameters = [], array! headers = []) -> array|string
    {
        var query, curl, body, response;
        
        //
        this->setOptions();

        //
        let query = http_build_query(parameters);

        //
        let curl = curl_init(url.(!empty query ? "?".query : null));

        //
        if !empty headers {
            var header; for header in headers {
                let this->options[CURLOPT_HTTPHEADER][] = header;
            } 
        }

        //
        curl_setopt_array(curl, this->options);

        //
        let body = (string) curl_exec(curl);

        //
        curl_close(curl);

        //
        let response = json_decode(body, true);

        if (json_last_error() === JSON_ERROR_NONE) {
            return (array) response;
        }

        return (string) body;
    }

    /**
     *  POST
     *  Should handle non array data parameters
     */
    public function post(string! url, var parameters = null, array! headers = []) -> array
    {
        var curl, body;
                
        //
        this->setOptions();

        //
        if is_array(parameters) {
            let parameters = json_encode(parameters);
        }

        //
        let curl = curl_init(url);

        //
        let this->options[CURLOPT_POST] = true;
        let this->options[CURLOPT_POSTFIELDS] = parameters;

        //
        if !empty headers {
            var header; for header in headers {
                let this->options[CURLOPT_HTTPHEADER][] = header;
            } 
        }

        //
        curl_setopt_array(curl, this->options);

        //
        let body = curl_exec(curl);
        
        if curl_error(curl) {
            return serialize([
                "url"   : url,
                "error" : curl_error(curl),
                "code"  : curl_getinfo(curl, CURLINFO_HTTP_CODE)
            ]);
        }

        //
        curl_close(curl);

        //
        return body;
    }

    /**
     *  PUT
     */
    public function put(string! url, array! parameters = [], array! headers = []) -> array
    {
        var curl, body;
                
        //
        this->setOptions();

        //
        let curl = curl_init(url);

        //
        let this->options[CURLOPT_CUSTOMREQUEST] = "PUT";
        let this->options[CURLOPT_POSTFIELDS] = json_encode(parameters);

        //
        if !empty headers {
            var header; for header in headers {
                let this->options[CURLOPT_HTTPHEADER][] = header;
            } 
        }

        //
        curl_setopt_array(curl, this->options);

        //
        let body = (string) curl_exec(curl);

        //
        curl_close(curl);

        //
        return (array) json_decode(body, true);
    }
    
    /**
     *  PATCH
     */
    public function patch(string! url, array! parameters = [], array! headers = []) -> array
    {
        var curl, body;
                
        //
        this->setOptions();

        //
        let curl = curl_init(url);

        //
        let this->options[CURLOPT_CUSTOMREQUEST] = "PATCH";
        let this->options[CURLOPT_POSTFIELDS] = json_encode(parameters);

        //
        if !empty headers {
            var header; for header in headers {
                let this->options[CURLOPT_HTTPHEADER][] = header;
            } 
        }

        //
        curl_setopt_array(curl, this->options);

        //
        let body = (string) curl_exec(curl);

        //
        curl_close(curl);

        //
        return (array) json_decode(body, true);
    }

    /**
     *  DELETE
     */
    public function delete(string! url, array! headers = []) -> array
    {
        var curl, body;
                
        //
        this->setOptions();

        //
        let curl = curl_init(url);

        //
        let this->options[CURLOPT_CUSTOMREQUEST] = "DELETE";

        //
        if !empty headers {
            var header; for header in headers {
                let this->options[CURLOPT_HTTPHEADER][] = header;
            } 
        }

        //
        curl_setopt_array(curl, this->options);

        //
        let body = (string) curl_exec(curl);

        //
        curl_close(curl);

        //
        return (array) json_decode(body, true);
    }

}