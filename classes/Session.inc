<?php

class Session {
    /**
     * create a session
     * @param $session_name
     * @param $session_value
     * @return mixed
     */
    public static function set($session_name, $session_value){
        return $_SESSION[$session_name] = $session_value;
    }

    /**
     * checks if the given session exists
     * @param $session_name
     * @return bool
     */
    public static function exists($session_name){
        return (isset($_SESSION[$session_name])) ? true : false;
    }

    /**
     * get a session value
     * @param $session_name
     * @return mixed
     */
    public static function get($session_name){
        return $_SESSION[$session_name];
    }

    /**
     * delete a session
     * @param $session_name
     * @return bool
     */
    public static function delete($session_name){
        if(self::exists($session_name)){
            unset($_SESSION[$session_name]);
            return true;
        }
        return false;
    }

    /**
     * flashes a session value, when the second time the session is get
     * @param $session_name
     * @param string $session_content
     * @return mixed
     */
    public static function flash($session_name, $session_content = ''){
        if(self::exists($session_name)){
            $session = self::get($session_name);
            self::delete($session_name);
            return $session;
        }else{
            self::set($session_name, $session_content);
        }
    }
} 