<?php

class Database{
    private static $_instance = null;
    private $_pdo,
            $_query,
            $_result,
            $_count = 0,
            $_error = false,
            $_is_object = true;

    /**
     * Database Constructor Method
     */
    public function __construct(){
        try{
            // connecting to database once upon instantiation
            $this->_pdo = new PDO("mysql:host=".Config::get('mysql/host').";dbname=".Config::get('mysql/db_name'),
                Config::get('mysql/username'), Config::get('mysql/password'));
        } catch(Exception $e){
            echo $e->getMessage();
            exit;
        }
    }

    /**
     * returns a single instance of Database Class
     * @return Database|null
     */
    public static function getInstance(){
        if(!isset(self::$_instance)){
            self::$_instance = new self;
        }
        return self::$_instance;
    }

    /**
     * executes query and returns an instance of Database
     * @param $sql
     * @param array $params
     * @return $this
     */
    public function query($sql, $params = array()){
        $this->_error = false;
        if($this->_query = $this->_pdo->prepare($sql)){
            if(count($params)){
                $x = 1;
                foreach($params as $param){
                    $this->_query->bindValue($x, $param);
                    $x++;
                }
            }
            if($this->_query->execute()){
                if($this->_is_object){
                    $this->_result = $this->_query->fetchAll(PDO::FETCH_OBJ);
                }else{
                    $this->_result = $this->_query->fetchAll(PDO::FETCH_ASSOC);
                }
                $this->_count = $this->_query->rowCount();
            }
        }else{
            $this->_error = true;
        }
        return $this;
    }

    /**
     * select records from a table
     * @param $table_name
     * @param array $where
     * @return $this|bool
     */
    public function select($table_name, $where = array()){
        if(is_array($where) && $where != null){
            return $this->dbAction("SELECT *", $table_name, $where);
        } else{
            $sql = "SELECT * FROM {$table_name}";
            if(!$this->query($sql)->getError()){
                return $this;
            }
        }

    }

    /**
     * insert record into a table
     * @param $table_name
     * @param array $data
     * @return bool
     */
    public function insert($table_name, $data = array()){
        if($count = count($data)){
            $columns = array_keys($data);
            $values = null;

            for($x = 1; $x <= $count; $x++){
                $values .= '?';
                if($x < $count){
                    $values .= ', ';
                }
            }

            $sql = "INSERT INTO {$table_name} (`". implode("`, `", $columns) ."`) VALUES ({$values})";
            if(!$this->query($sql, $data)->getError()){
                return true;
            }
        }
        return false;
    }

    /**
     * update record of a table
     * @param $table_name
     * @param array $data
     * @param $id
     * @return bool
     */
    public function update($table_name, $data = array(), $where = array()){
        if($count = count($data)){
            $set = '';
            $x = 1;
            foreach($data as $column => $value){
                $set .= "`{$column}` = ?";
                if($x < $count){
                    $set .= ", ";
                }
                $x++;
            }

            if(count($where) == 3){
                $operators = array('=', '<', '>', '>=', '<=', '!=');

                $column_name = trim($where[0]);
                $operator = trim($where[1]);
                $value = trim($where[2]);
            }

            $sql = "UPDATE `{$table_name}` SET {$set} WHERE {$column_name} {$operator} {$value}";
            if(!$this->query($sql, array_values($data))->getError()){
                return true;
            }
        }
        return false;
    }

    /**
     * delete records from a table
     * @param $table_name
     * @param array $where
     * @return $this|bool
     */
    public function delete($table_name, $where = array()){
        return $this->dbAction("DELETE", $table_name, $where);
    }

    /**
     * perform a requested SQL action
     * @param $action
     * @param $table_name
     * @param array $where
     * @return $this|bool
     */
    private function dbAction($action, $table_name, $where = array()){
        if(count($where) == 3){
            $operators = array('=', '<', '>', '>=', '<=', '!=');

            $column_name = trim($where[0]);
            $operator = trim($where[1]);
            $value = trim($where[2]);

            if(in_array($operator, $operators)){
                $sql = "{$action} FROM {$table_name} WHERE {$column_name} {$operator} ?";
                if(!$this->query($sql, array($value))->getError()){
                    return $this;
                }
            }
        }
        return false;
    }

    /**
     * returns Database error status
     * @return bool
     */
    public function getError(){
        return $this->_error;
    }

    /**
     * returns current result set
     * @return mixed
     */
    public function getResult(){
        return $this->_result;
    }

    public function getRow(){
        return $this->getResult()[0];
    }

    /**
     * returns number of affected rows
     * @return int
     */
    public function getCount(){
        return $this->_count;
    }

    /**
     * return pdo connection
     * @return mixed
     */
    public function pdo(){
        return $this->_pdo;
    }

    /**
     * set the result type [false for array record, true for object record]
     * @param bool $is_object
     */
    public function setObject($is_object = true){
        if(!$is_object){ $this->_is_object = false; }
        else{ $this->_is_object = true; }
    }
}