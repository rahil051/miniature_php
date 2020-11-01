<?php

class Hash {
    /**
     * hash a password using a sha256 algorithm encryption technique
     * @param $string
     * @param string $salt
     * @return string
     */
    public static function generateHash($string, $salt = ''){
        return hash('sha256', $string . $salt);
    }

    /**
     * generate a salt for the hash
     * @param $length
     * @return string
     */
    public static function generateSalt($length){
        return mcrypt_create_iv($length);
    }

    /**
     * generate a unique hash
     * @return string
     */
    public static function generateUnique(){
        return self::generateHash(uniqid());
    }
} 