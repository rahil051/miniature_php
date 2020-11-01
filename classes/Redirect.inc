<?php

class Redirect {
    /**
     * redirect to wrapper
     * @param type $location
     */
    public static function to($location = null){
        if($location){
            if(is_numeric($location)){
                switch($location){
                    case 404:
                        header('HTTP/1.1 404 Not Found');
                        include Config::get('redirect/404');
                        exit;
                        break;
                }
            }
            header('Location: ' . $location);
            exit;
        }
    }
} 