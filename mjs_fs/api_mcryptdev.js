load("api_i2c.js")
// I2C address for the crypto-chip, atecc508a is usually 96
let I2Caddr = 96;
let mcryptdev = {
    add: ffi('int add(int, int)'),
    readInitBit: function(){
        let bus_addr = I2C.get();
        // .read(i2c bus object, i2c address, number of bits to read, [bool] release bus when complete?)
        return I2C.read(bus_addr, I2Caddr, 2, true);
    },
    generateRandom: ffi('int generateRandom()'),
    
};