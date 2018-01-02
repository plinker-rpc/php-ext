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

namespace Plinker\Endpoint;

/**
 * Lxd\Endpoints\Images
 *
 * Provides image facilities to the API
 * @see https://github.com/lxc-systems/lxd/blob/master/lxd/endpoints/images.zep
 */
final class System
{    
    
    protected $host_os;

    /**
     * Class construct.
     *
     * @param  array          config Config array which holds object configuration
     * @param  <Lxd\Lib\Curl> curl
     * @return void
     */
    public function __construct(array! config) -> void
    {
        let this->host_os = trim(strtoupper(strstr(php_uname(), " ", true)));
    }

    /**
     * Get diskspace
     *
     * @param  string $path
     * @return int
     */
    public function disk_space(string! path = "/")
    {
        var ds = disk_total_space(path),
            df = disk_free_space(path);

        return (df > 0 && ds > 0 && df < ds) ? floor(df/ds * 100) : 0;
    }
    
    /**
     * Get total diskspace
     *
     * @param  string $path
     * @return int
     */
    public function total_disk_space(string! path = "/")
    {
        return disk_total_space(path);
    }
}
