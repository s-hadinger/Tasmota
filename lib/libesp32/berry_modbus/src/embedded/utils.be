#-
Utils.

This file defines the util functions and Constant Variables.

@file       utils.be

@date       November 15, 2023

@note       This file is writen in Berry Language. 
@note       For more information see https://berry.readthedocs.io/en/latest/
@note       Short Manual: https://github.com/Skiars/berry_doc/releases/download/latest/berry_short_manual.pdf
@note       Berry on Tasmota: https://tasmota.github.io/docs/Berry/
-#
import math
import string

var utils = module("utils")
utils.is_level_available = def (context)
    #- 
        check if level is available

        @param context Measuring_context
        @return true if level is available
    -#
    return context && context.get_component(context.protocol_module.LEVEL_BOARD_STATE) != nil

end

utils.is_number = def (value)
    #- 
        check if value is number

        @param value value to check
        @return true if value is number
    -#
    return value != nil && (type(value) == 'real' || type(value) == 'int')

end

utils.max = def (a, b)
    #- 
        return max of a and b

        @param a value a
        @param b value b
        @return max of a and b
    -#
    if a > b
        return a
    end
    return b
end

utils.min = def (a, b)
    #- 
        return min of a and b

        @param a value a
        @param b value b
        @return min of a and b
    -#
    if a < b
        return a
    end
    return b
end

utils.get_flow_volume = def(context)
    #- 
        get flow volume volume if available or nil

        @param context Measuring_context
        @return flow volume or nil
    -#
    if context == nil
        return
    end
    var flow_num = context.get_component(context.protocol_module.FLOWMETER_VOLUME)
    if flow_num
        return flow_num.value
    end
    return nil
end

utils.bitand = def (a, b)
    #- 
        bitwise and of a and b

        @param a value a
        @param b value b
        @return true bitwise and of a and b
    -#
    var result = 0
    var bitval = 1
    while a > 0 && b > 0
        if a % 2 == 1 && b % 2 == 1 # test the rightmost bits
            result = result + bitval # set the current bit
        end
        bitval = bitval * 2 # shift left
        a = int(a/2) # shift right
        b = int(b/2)
    end
    return result != 0
end

utils.calculate_mean = def (data)
    #-
        Calculates the mean of a data set.
        
        @param data The data set.
        @return The mean.
    -#
    var sum = 0
    for e:data
        sum += e
    end
    return sum / real(size(data))
end

utils.calculate_covariance = def(x, y)
    #-
        Calculates the covariance of two data sets.
        
        @param x The first data set.
        @param y The second data set.
        @return The covariance.
    -#
    assert(size(x) == size(y))
    var n = size(x)
    var x_mean = utils.calculate_mean(x)
    var y_mean = utils.calculate_mean(y)
    var cov = 0.0
    for i:0..size(x)
        cov += (x[i] - x_mean) * (y[i] - y_mean)
    end
    return cov / n
end
    
utils.calculate_standard_deviation = def(data)
    #-
        Calculates the standard deviation of a data set.

        @param data The data set.
    -#
    var n = size(data)
    var mean = utils.calculate_mean(data)
    var sum_sq_diff = 0.0
    for e:data
        sum_sq_diff += (e - mean) * (e - mean)
    end
    return math.sqrt(sum_sq_diff / n)

end
    
utils.calculate_correlation = def (x, y)
  #-
    Calculates the correlation coefficient of two data sets.
    
    @param x The first data set.
    @param y The second data set.
    @return The correlation coefficient.
  -#
    assert(size(x) == size(y))
    var cov = utils.calculate_covariance(x, y)
    var std_x = utils.calculate_standard_deviation(x)
    var std_y = utils.calculate_standard_deviation(y)
    return cov / (std_x * std_y)

end
    
#-
    int main() {
        double x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        double y[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        size_t n = sizeof(x) / sizeof(x[0]);

        double correlation = calculate_correlation(x, y, n);
        printf("Korrelationskoeffizient: %f\n", correlation);
        
        return 0;
    }
-#

utils.brix_temperature_compensation = def (measured_brix, sample_temperature)
    #-
        Compensates the Brix value for temperature.
        
        @param measured_brix The Brix value measured at the sample temperature.
        @param sample_temperature The temperature of the sample in degrees Celsius.
        @return The temperature-compensated Brix value.
    -#

    # Standard temperature in degrees Celsius
    var standard_temperature = 20.0

    # Coefficient for temperature compensation
    var coefficient = 0.0002

    # Calculate the corrected Brix value
    return measured_brix - (coefficient * (sample_temperature - standard_temperature))
end

utils.is_level_flag_valid = def (level_flags_component, context)
    #-
        Check if level flag are valid

        @param level_flags_component Level_flags_component
        @param context Measuring_context
        @return Error_msg or nil if valid
    -#
    if level_flags_component == nil || !utils.is_number(level_flags_component.value)
        return context.error.level_flags
    end
    var level_flags = level_flags_component.value
    
    if (level_flags & 0x80) != 0
        # ultrasonic not available
        return context.error.level_ultrasonic_not_available
    end

    if (level_flags & 0x01) != 0
        return context.error.level_air_leak
    end
    
    if (level_flags & 0x08) != 0
        # air pressure warning
        return context.error.air_pressure
    end

    if (level_flags & 0xFE) != 0
        # level critical error or unknown
        return context.error.level_error
    end
end

utils.trimToLimits = def (from, min, max)
    #-  
        trims the value to the limits
        @param from - value to trim
        @param min - minimum value
        @param max - maximum value
        @return trimmed value or nil
    -#
    var value = number(from)
    if min > value
        return min
    elif max < value
        return max
    else
        return value
    end
end
  
utils.setterStr = def (value)
    #- 
        converts the string to the byte array
        @param value - string to convert
        @return byte array or nil
    -#
    if !value return nil end
    var byte_array = []
    for i:0..size(value)-1
        byte_array.push(string.byte(value[i]))
    end
    return byte_array.tostring() 
end
  
utils.getterValue = def (msg)
    #- 
        extracts the value from the modbus received message
        @param msg - json message to extract the value from
        @return value or nil
    -#
    var value = nil
    if type(msg) == "instance" && msg.contains("ModbusReceived") 
        var rec = msg["ModbusReceived"]
        if rec.find("Values")
            value = rec["Values"]
            if size(value) == 0 
                value = nil
            end
        end
    end
    return value
end
  
utils.getterHex = def(msg)
    #- 
      converts the modbus received message from byte array to the hex string
      @param msg - json message to extract the value from
      @return hex string
    -#
    var res = ""
    var value = utils.getterValue(msg)
    if value == nil return str end
    for i:0..size(value)-1
        res = string.format(str + "%x", value[i])
    end
    return res
end
  
utils.getterFirmware = def (msg)
    #- 
      converts the modbus received message from byte array to the hex firmware string
      @param msg - json message to extract the value from
      @todo integrate firmware version
      @return hex string with dots
    -#
    #hex=string.format("%06x",tonumber(from))
    #hv=tonumber(string.sub(hex,1, 2),16)
    #lv=tonumber(string.sub(hex,3, 4),16)
    #pv=tonumber(string.sub(hex,5, 6), 16)
    #return  format("%x.%x.%x",hv, lv, pv)
end
  
utils.getterLtlPressureSensorType = def (register)
      #- 
        converts the modbus received message from byte array to the pressure sensor type string
        
        @todo integrate pressure sensor type
      -#
      #register = tonumber(register)
      #local name = 'UNKNOWN'
      #if 1 == register then
      #    name = 'MPX2100DB'
      #elseif 2 == register then
      #    name = 'AG216-025KG'
      #elseif 4 == register then
      #    name = '2066-2103'
      #end
      #return string.format('%s (%s)', name, register)
end
  
utils.getterStr = def (msg)
    #- 
        converts the modbus received message to string
        @param msg - json message to extract the value from
        @return string
    -#
    var res = ""
    var value = utils.getterValue(msg)
    if value == nil return str end
    for i:0..size(value)-1
        res = string.format(str + "%c", value[i])
    end
    return res
end
  
utils.trimToBits = def (value, bitsNumber, unsigned)
    #- 
        trims the value to the bits number
        @param value - value to trim
        @param bitsNumber - number of bits to trim to
        @param unsigned - true if unsigned value
        @return trimmed value
    -#
    if unsigned
        return utils.trimToLimits(value, 0, math.pow(2, bitsNumber)-1)
    else
        return utils.trimToLimits(value, -math.pow(2, bitsNumber-1), math.pow(2, bitsNumber-1)-1)
    end
end
  
utils.setterUInt = def (from, multiplier, bitsNumber)
    #- 
        converts the value to the byte array
        @param from - value to convert
        @param multiplier - multiplier to apply
        @param bitsNumber - number of bits to trim to
        @return byte array or nil
    -#
    if !from return nil end
    var ret = number(from)
    if ret == nil return nil end # error("setterUInt ".. from .." value NAN")
    var res_list = [
        utils.trimToBits(math.floor(ret * multiplier), bitsNumber, true)
    ]
    return res_list.tostring()
end
  
utils.getterUInt = def (from, divider, bitsNumber)
    #- 
        converts the byte array to the value
        @param from - byte array to convert
        @param divider - divider to apply
        @param bitsNumber - number of bits to trim to
    -#
    var value = utils.getterValue(from)
    if value == nil return nil end
    value = value[0]
    var ret = math.floor(utils.trimToBits(value, bitsNumber, true))
    return string.format("%f",ret / divider)
end
  
utils.setterInt = def (from, multiplier, bitsNumber)
    #- 
        converts the value to the byte array
        @param from - value to convert
        @param multiplier - multiplier to apply
        @param bitsNumber - number of bits to trim to
        @return byte array or nil
    -#
    if !from return nil end
    var ret = number(from)
    if ret == nil return nil end # error("setterInt ".. from .." value NAN")
    ret = utils.trimToBits(math.floor(ret*multiplier), bitsNumber, false)
    if 0 > ret
        ret = math.floor(math.pow(2, bitsNumber) + ret)
    end
    var res_list = [
        utils.trimToBits(ret, bitsNumber, true)
    ]
    return res_list.tostring()
end
 
utils.getterInt = def (from, multiplier, bitsNumber)
    #- 
        converts the byte array to the value
        @param from - byte array to convert
        @param multiplier - multiplier to apply
        @param bitsNumber - number of bits to trim to
        @return value or nil
    -#
    var value = utils.getterValue(from)
    if value == nil return nil end
    value = value[0]
    var ret = math.floor(utils.trimToBits(value, bitsNumber, true))
    if math.pow(2, bitsNumber-1) <= ret
        ret = ret - math.pow(2, bitsNumber)
    end
    return string.format("%f",ret / multiplier)
end

utils.setterAMQPConnectionState = def (from)
    #- 
        converts the value from enum string to the byte array
        @param from - value to convert
        @return byte array or nil
    -#
    var ret = 0
    if string.find(from, "connecting") != nil
        ret = 1
    elif string.find(from, "connected") != nil
        ret = 2
    elif string.find(from, "disconnected") != nil
        ret = 3
    else
        ret = 0 # uninitialized
    end
    var res_list = [
        string.format("%i",ret)
    ]
    return res_list.tostring()
end
  
utils.dateSetter = def (v)
    #- 
        converts the value from date string to the byte array
        @param v - value to convert
        @return byte array or nil
    -#
    var y = string.format("%.4x", number(string.sub(v, 1, 4)))
    var m = string.format("%.4x", number(string.sub(v, 5, 6)))
    var d = string.format("%.4x", number(string.sub(v, 7, 8)))
    var res_list = [
        number(string.format("%s%s%s", y, m, d), 16)
    ]
    return res_list.tostring()
end
  
utils.timeSetter = def (v)
    #- 
        converts the value from time string to the byte array
        @param v - value to convert
        @return byte array or nil
    -#
    var res = ""
    var ids = [1,6,2]
    for i:0..size(ids)-1
        res = string.format("%s%.4x", res, number(string.sub(v, i, i + 1)))
    end
    var res_list = [
        number(res, 16)
    ]
    return res_list.tostring()
end
  
# air pressure convertors
utils.mpx2100db_mBar = def (millivolts)
    #- 
        converts the value from millivolts to mBar
        @param millivolts - value to convert
        @return mBar or nil
    -#
    var sensitivity = 0.4
    var offset = 1500
    var ampl_K = 667.7  # on-board amplifier coefficient, Rg=75 Ohm
    var kPa = (1.0 * number(millivolts) - offset) / ampl_K / sensitivity
    return kPa * 10  # Convert to mBar
end

utils.mBar2m = def (mBar)
    #- 
        converts the value from mBar to meters
        
        Density of water is 997
        
        @f$ h = p / ro / g @f$
        
        @f$ p(Pa) = ro * g * h @f$
        
        @param mBar - value to convert
        @return meters or nil
    -#
    var g = 9.8
    var pa = mBar * 100 # Pressure in pascals
    var ro = 997        # density of water
  
    return pa / ro / g
end
  
utils.makeColonPixelArray = def (s)
    #-  
        converts the string to the colon pixel array
    
        @todo integrate colon pixel array
    -#
    return s

end
  
utils.getterDeviceInfoName = def (from)
    #- 
        converts the value from hex to the device info name string
        @param from - value to convert
        @return device info name string or nil
    -#
    var data = utils.getterUInt(from, 1, 16)
    var name = 'UNKNOWN'
    if 0x01 == data
        name = 'LTS-Refractometer'
    elif 0x02 == data
        name = 'LTS-Supervisor'
    elif 0x10 == data
        name = 'LTE'
    elif 0x20 == data
        name = 'LTF'
    end
    return format('%s (%i)', name, data)
end
  
utils.getterHexVersionWithDots = def (from)
    #- 
        converts the value from hex to the version string with dots
        @param from - value to convert
        @return version string with dots or nil
    -#
    var ret = utils.getterUInt(from, 1, 16)
    return format('%s.%s.%s', (ret & 0xf00) >> 8, (ret & 0x0f0) >> 4, (ret & 0x00f))
end

utils.getterInt8_1 = def (from)
    #- 
        converts the byte array to int8 devided by 1
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1, 8)
end

utils.getterInt8_10 = def (from)
    #- 
        converts the byte array to int8 devide by 10
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 10, 8)
end

utils.getterInt16_1 = def (from)
    #- 
        converts the byte array to int16 devide by 1
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1, 16)
end

utils.getterInt16_10 = def (from)
    #- 
        converts the byte array to int16 devide by 10
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 10, 16)
end

utils.getterInt16_100 = def (from)
    #- 
        converts the byte array to int16 devide by 100
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 100, 16)
end

utils.getterInt16_1000 = def (from)
    #- 
        converts the byte array to int16 devide by 1000
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1000, 16)
end

utils.getterInt32_1 = def (from)
    #- 
        converts the byte array to int32 devide by 1
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1, 32)
end

utils.getterInt32_10 = def (from)
    #- 
        converts the byte array to int32 devide by 10
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 10, 32)
end

utils.getterInt32_100 = def (from)
    #- 
        converts the byte array to int32 devide by 100
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 100, 32)
end

utils.getterInt32_1000 = def (from)
    #- 
        converts the byte array to int32 devide by 1000
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1000, 32)
end

utils.getterInt32_1000000 = def (from)
    #- 
        converts the byte array to int32 devide by 1000000
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterInt(from, 1000000, 32)
end

utils.getterUInt8 = def (from)
    #- 
        converts the byte array to uint8 value
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1, 8)
end

utils.getterUInt1_1 = def (from)
    #- 
        converts the byte array to uint1 value
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1, 1)
end

utils.getterUInt16_1 = def (from)
    #-
        converts the byte array to uint16 devided by 1
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1, 16)
end

utils.getterUInt16_10 = def (from)
    #-
        converts the byte array to uint16 devided by 10
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 10, 16)
end

utils.getterUInt16_100 = def (from)
    #-
        converts the byte array to uint16 devided by 100
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 100, 16)
end

utils.getterUInt16_1000 = def (from)
    #-
        converts the byte array to uint16 devided by 1000
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1000, 16)
end

utils.getterUInt32_1 = def (from)
    #-  
        converts the byte array to uint32 devide by 1
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1, 32)
end

utils.getterUInt32_10 = def (from)
    #-  
        converts the byte array to uint32 devide by 10
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 10, 32)
end

utils.getterUInt32_100 = def (from)
    #-  
        converts the byte array to uint32 devide by 100
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 100, 32)
end

utils.getterUInt32_1000 = def (from)
    #-  
        converts the byte array to uint32 devide by 1000
        @param from - byte array to convert
        @return value or nil
    -#
    return utils.getterUInt(from, 1000, 32)
end

utils.setterUInt16_1 = def (from)
    #- 
        converts the uint16 value multiply by 1 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1, 16)
end

utils.setterUInt16_10 = def (from)
    #- 
        converts the uint16 value multiply by 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 10, 16)
end

utils.setterUInt16_1000 = def (from)
    #- 
        converts the uint16 value multiply by 1000 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1000, 16)
end

utils.setterInt16_100 = def (from)
    #- 
        converts the int16 value multiply by 100 to the byte array
        @return byte array or nil
    -#
    return utils.setterInt(from, 100, 16)
end

utils.setterInt16_1000 = def (from)
    #- 
        converts the int16 value multiply by 1000 to the byte array
        @return byte array or nil
    -#
    return utils.setterInt(from, 1000, 16)
end

utils.setterUInt32_1 = def (from)
    #- 
        converts the uint32 value multiply by 1 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1, 32)
end

utils.setterUInt32_10 = def (from)
    #- 
        converts the uint32 value multiply by 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 10, 32)
end

utils.setterUInt32_100 = def (from)
    #- 
        converts the uint32 value multiply by 100 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 100, 32)
end

utils.setterUInt32_1000 = def (from)
    #- 
        converts the uint32 value multiply by 1000 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1000, 32)
end

utils.setterUInt32_1_ceil_0_4096 = def (from)
    #- 
        converts the uint32 value multiply by 1000 ceil between 0 and 4095 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 0, 4095), 1, 32)
end

utils.setterUInt32_1_ceil_1_10 = def (from)
    #- 
        converts the uint32 value multiply by 1 ceil between 1 and 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 1, 10), 1, 32)
end

utils.setterUInt32_10_ceil_1_10 = def (from)
    #- 
        converts the uint32 value multiply by 10 ceil between 1 and 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 1, 10), 10, 32)
end

utils.setterUInt32_10_ceil_0_127 = def (from)
    #- 
        converts the uint32 value multiply by 10 ceil between 1 and 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 0, 127), 10, 32)
end

utils.setterUInt32_100_ceil_001_099 = def (from)
    #- 
        converts the uint32 value multiply by 100 ceil between 0.01 and 0.99 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 0.01, 0.99), 100, 32)
end

utils.setterUInt32_1000_ceil_0_100 = def (from)
    #- 
        converts the uint32 value multiply by 1000 ceil between 0 and 100 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(utils.trimToLimits(from, 0, 100), 1000, 32)
end

utils.setterInt32_1 = def (from)
    #- 
        converts the int32 value multiply by 1 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1, 32)
end

utils.setterInt32_10 = def (from)
    #- 
        converts the int32 value multiply by 10 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 10, 32)
end

utils.setterInt32_100 = def (from)
    #- 
        converts the int32 value multiply by 100 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 100, 32)
end

utils.setterInt32_1000 = def (from)
    #- 
        converts the int32 value multiply by 1000 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1000, 32)
end

utils.setterInt32_1000000 = def (from)
    #- 
        converts the int32 value multiply by 1000000 to the byte array
        @return byte array or nil
    -#
    return utils.setterUInt(from, 1000000, 32)
end

utils.setterInt32_1_ceil_400_2147483647 = def (from)
    #- 
        converts the int32 value multiply by 1 ceil between 400 and 2147483647 to the byte array
        @return byte array or nil
    -#
    return utils.setterInt(utils.trimToLimits(from, 400, 2147483647), 1, 32)
end

utils.char_replace = def (input_str, char_to_find, char_to_replace)
    #-  
        replaces the char in the string

        @param input_str - string to replace the char in
        @param char_to_find - char to find
        @param char_to_replace - char to replace
        @return string with replaced char
    -#
    var res = ""
    for i: 0 .. (size(str) - 1)
        if char_to_find == input_str[i]
            res += char_to_replace
        else
            res += input_str[i]
        end
    end
    return res
end

utils.list_sort = def (arr)
    #-
        Bubble sort of a list, ascending order

        @param arr The list to sort
        @return The sorted list
    -#
    for i:1..size(arr)-1
        var k = arr[i]
        var j = i
        while (j > 0) && (arr[j-1] > k)
            arr[j] = arr[j-1]
            j -= 1
        end
        arr[j] = k
    end
    return arr
end

#@ solidify:utils,weak

return utils