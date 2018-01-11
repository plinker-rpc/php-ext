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

final class Signer
{

    private config;

    /**
     *
     */
    public function __construct(array! config = []) -> void
    {
        //
        let this->config = array_merge([
            "secret" : null
        ], config);

        // hash secret
        if isset this->config["secret"] {
            let this->config["secret"] = hash("sha256", gmdate("h").this->config["secret"]);
        }
    }

    /**
     *
     */
    private function encrypt(string! plaintext, string! password) -> string
    {
        string method     = "AES-256-CBC";
        string key        = (string) hash("sha256", password, true);
        string iv         = (string) openssl_random_pseudo_bytes(16);
        string ciphertext = (string) openssl_encrypt(plaintext, method, key, OPENSSL_RAW_DATA, iv);
        
        string hash = (string) hash_hmac("sha256", ciphertext, key, true);

        return base64_encode(iv . hash . ciphertext);
    }
    
    /**
     *
     */
    private function decrypt(string! ciphertext, string! password) -> string|null
    {
        let ciphertext    = base64_decode(ciphertext);
        
        string method     = "AES-256-CBC";
        string iv         = substr(ciphertext, 0, 16);
        string hash       = substr(ciphertext, 16, 32);
        string ciphertext = substr(ciphertext, 48);
        string key        = (string) hash("sha256", password, true);

        if hash_hmac("sha256", ciphertext, key, true) !== hash {
            return null;
        }

        return openssl_decrypt(ciphertext, method, key, OPENSSL_RAW_DATA, iv);
    }
    
    /**
     *
     */
    public function encode(array! data) -> array
    {
        string data = serialize(data);
            
        return [
            "data" : this->encrypt(data, this->config["secret"]),
            "token": hash_hmac(
                "sha256",
                data,
                this->config["secret"]
            )
        ];
    }

    /**
     *
     */
    public function decode(array! data) -> array|null
    {
        let data["data"] = this->decrypt(data["data"], this->config["secret"]);
        
        //
        if hash_hmac(
            "sha256",
            data["data"],
            this->config["secret"]
        ) == data["token"] {
            return (array) unserialize(data["data"]);
        } else {
            return null;
        }
    }
}