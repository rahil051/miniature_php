<?php

class Validation {
    private $_db = null;
    private $_passed = false;
    private $_errors = array();

    /**
     * Validation Constructor
     * instantiates the Database class upon constructor call
     */
    public function __construct(){
        
        $this->_db = Database::getInstance();
    }

    /**
     * validate the inputs
     * @param $source
     * @param array $items
     */
    public function check($source, $items = array()){
        foreach($items as $item => $rules){
            $value = $source[$item];
            foreach($rules as $rule => $rule_value){
                if($rule == 'required' && empty($value)){
                    $this->addError("{$item} is required");
                }
                else if(!empty($value)){
                    $rule_value = trim($rule_value);
                    switch($rule){
                        case 'min':
                            if(strlen($value) < $rule_value){
                                $this->addError("{$item} must minimum of {$rule_value} characters.");
                            }
                            break;
                        case 'max':
                            if(strlen($value) > $rule_value){
                                $this->addError("{$item} must maximum of {$rule_value} characters.");
                            }
                            break;
                        case 'unique':
                            $check_for_unique = $this->_db->select($rule_value, [$item, '=', $value]);
                            if($this->_db->getCount($check_for_unique)){
                                $this->addError("{$item} already exists");
                            }
                            break;
                        case 'matches':
                            if($value != $source[$rule_value]){
                                $this->addError("{$rule_value} does not matches {$item}");
                            }
                            break;
                        case 'numeric':
                            if(!is_numeric($value)){
                                $this->addError("{$item} is not a numeric value");
                            }
                            break;
                        case 'valid_email':
                            if(!filter_var($value, FILTER_VALIDATE_EMAIL)){
                                $this->addError("{$item} is not a valid email");
                            }
                        default:
                            break;
                    }
                }
            }
        }
        if(empty($this->_errors)){
            $this->_passed = true;
        }
    }

    /**
     * check if the validation is passed
     * @return bool
     */
    public function isPassed(){
        return $this->_passed;
    }

    /**
     * add errors to the $_errors instance array
     * @param $error
     */
    public function addError($error){
        $this->_errors[] = $error;
    }

    /**
     * get all the errors
     * @return array
     */
    public function getErrors(){
        return $this->_errors;
    }
}