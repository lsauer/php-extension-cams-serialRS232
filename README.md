php-extension: CAMS, a serial RS232 wrapper
==============================

>A php-extension that provides parallel and optionally, serial-port/RS232 access to PHP for the Computer Aided Measuring Station (CAMS) project. Go to the `CAMS` [repository](https://github.com/lsauer/CAMS "") to download or fork the php web-appplication codebase and related resources.

**author**: Lorenz Lo Sauer 2002; www.lsauer.com   
**website**: https://github.com/lsauer/php-extension-cams-serialRS232   
**license**: GPL license, Graphics: CC-BY-SA   

**description**: As PHP 4.x does not provide hardware-port access through any library, a PHP extension was created. PHP allows easy extensibility through a dynamic link library/shared object (dll/so), when adhering to  `ZEND-interface specifications`. Once compiled the dll/so is loaded dynamically at run time and can be accessed through the `exported function names` defined in the `php_cams.h` header-file:

```cpp
ZEND_FUNCTION(cams_open);
ZEND_FUNCTION(cams_close);
ZEND_FUNCTION(cams_outp);
ZEND_FUNCTION(cams_inp);
ZEND_FUNCTION(cams_getport);
```

### Graphics


#### CAMS 3D View

![CAMS Casing 3D Design](https://googledrive.com/host/0ByqWUM5YoR35eWRRbVFqNFVibGM/cams_white.jpg "CAMS Casing 3D Design")

#### Principal Data flow

![principal data flow](https://googledrive.com/host/0ByqWUM5YoR35eWRRbVFqNFVibGM/flow_chart_data_cams.jpg "")

This flowchart shows the principal steps required for converting analog measurements to a digitally sampled signal via an n-bit Analog Digital Converter (ADC). The digital data is send to a parallel interface by mapping the opto-decoupled, parallel ADC output pins to the parallel port. The data is sampled and stored in a database, creating a time-series of sensor data, to be visualized on a PC.

#### Actual Data Flow

![Data flow](https://googledrive.com/host/0ByqWUM5YoR35eWRRbVFqNFVibGM/software_flow_cams.jpg "")


#### CAMS project outline

![CAMS project outline](https://googledrive.com/host/0ByqWUM5YoR35eWRRbVFqNFVibGM/overview_cams.png "")