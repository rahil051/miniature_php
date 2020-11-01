<?php

class Config {
    /**
     * get config value
     * @param type $path
     * @return string|boolean
     */
    public static function get($path = null){
        if($path){
            $error_path = $path;
            $config = $GLOBALS['config'];
            $path = explode('/', $path);

            foreach($path as $bit){
                if(isset($config[$bit])){
                    $config = $config[$bit];
                } else {
                    echo "Error: undefined credential -> (". $error_path .")";
                    exit;
                }
            }
            return $config;
        }
        return false;
    }
} 