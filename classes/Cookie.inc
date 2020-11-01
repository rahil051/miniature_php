<?php 

class Cookie {
    /**
     * check if a certain cookie exists
     * @param type $name
     * @return type
     */
    public static function exists($name){
        return (isset($_COOKIE[$name])) ? true : false;
    }

    /**
     * set a cookie
     * @param type $name
     * @param type $value
     * @param type $expiry
     * @return boolean
     */
    public static function set($name, $value, $expiry){
        if(setcookie($name, $value, time() + $expiry, '/')){
            return true;
        }
        return false;
    }

    /**
     * get a cookie value
     * @param type $name
     * @return type
     */
    public static function get($name){
        return $_COOKIE[$name];
    }

    /**
     * delete a cookie
     * @param type $name
     * @return boolean
     */
    public static function delete($name){
        if(setcookie($name, '', time() - 1)){
            return true;
        }
        return false;
    }
} 