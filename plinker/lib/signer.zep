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

namespace Plinker\Lib;

final class Signer
{

    private config;
    private options;

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
        var method = "AES-256-CBC";
        var key = hash("sha256", password, true);
        var iv = openssl_random_pseudo_bytes(16);

        var ciphertext = openssl_encrypt(plaintext, method, key, OPENSSL_RAW_DATA, iv);
        var hash = hash_hmac("sha256", ciphertext, key, true);

        return base64_encode(iv . hash . ciphertext);
    }

    /**
     *
     */
    private function decrypt(string! ciphertext, string! password) -> string|null
    {
        var method = "AES-256-CBC";
        let ciphertext = base64_decode(ciphertext);
        var iv = substr(ciphertext, 0, 16);
        var hash = substr(ciphertext, 16, 32);
        var ciphertext = substr(ciphertext, 48);
        var key = hash("sha256", password, true);

        if (hash_hmac("sha256", ciphertext, key, true) !== hash) {
            return null;
        }

        return openssl_decrypt(ciphertext, method, key, OPENSSL_RAW_DATA, iv);
    }

    /**
     *
     */
    public function encode(array! data) -> array
    {
        return [
            "data" : this->encrypt(serialize(data), this->config["secret"]),
            "token": hash_hmac(
                "sha256",
                serialize(data),
                this->config["secret"]
            )
        ];
    }

    /**
     *
     */
    public function decode(array! data) -> string|null
    {
        let data["data"] = this->decrypt(data["data"], this->config["secret"]);

        //
        if (hash_hmac(
            "sha256",
            data["data"],
            this->config["secret"]
        ) == data["token"]) {
            return unserialize(data["data"]);
        } else {
            return null;
        }
    }
}