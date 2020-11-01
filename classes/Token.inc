<?php

class Token {
    /**
     * generate a random hash and store it into token session
     * @return type
     */
    public static function generate(){
        return Session::set(Config::get('session/token_name'), md5(uniqid()));
    }

    /**
     * check if the certain token exists in the session
     * @param type $token
     * @return boolean
     */
    public static function check($token){
        $token_name = Config::get('session/token_name');
        if(Session::exists($token_name) && $token === Session::get('token')){
            Session::delete($token_name);
            return true;
        }
        return false;
    }
}