<?php

class Input {
    /**
     * checks if an input value exists
     * @param string $type
     * @return bool
     */
    public static function exists($type = 'post'){
        switch($type){
            case 'post':
                return (!empty($_POST)) ? true : false;
                break;

            case 'get':
                return (!empty($_GET)) ? true : false;
                break;

            default:
                return false;
                break;
        }
    }

    /**
     * sanitize/clean an input value
     * @param $input_value
     * @return string
     */
    public static function sanitize($input_value){
        $cleaned_value = htmlentities($input_value, ENT_QUOTES, 'UTF-8');
        return $cleaned_value;
    }

    /**
     * sanitize all inputs from a form
     * @param $inputType
     * @return array|bool
     */
    public static function sanitizeAttributes($inputType = 'post'){
        $cleanedValues = array();
        switch ($inputType) {
            case 'post':
                foreach($_POST as $postKey => $postValue){
                    $cleanedValues[$postKey] = self::sanitize($postValue);
                }
                return $cleanedValues;
                break;
            
            case 'get':
                foreach ($_GET as $getKey => $getValue) {
                    $cleanedValues[$getKey] = self::sanitize($getValue);
                }
                return $cleanedValues;
                break;

            default:
                return false;
                break;
        }
    }

    /**
     * get an input value
     * @param $name
     * @return string
     */
    public static function get($name){
        if(isset($_POST[$name])) { return self::sanitize($_POST[$name]); }
        else if(isset($_GET[$name])) { return self::sanitize($_GET[$name]); }
        else return '';
    }
} 