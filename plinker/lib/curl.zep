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
            CURLOPT_ENCODING       : "gzip",
            CURLOPT_HTTPHEADER     : [
                "Content-Type: application/json"
            ]
        ];
    } 

    /**
     *  POST
     */
    public function post(string! url, var parameters = null, array! headers = []) -> string
    {
        var curl, body;
                
        //
        this->setOptions();

        //
        if is_array(parameters) {
            let parameters = json_encode(parameters);
            let parameters = gzdeflate(parameters, 9);
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

}