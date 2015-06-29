LaunchPad Energia M2X API Client
================================

The LaunchPad Energia library is used to send/receive data to/from [AT&amp;T's M2X Data Service](https://m2x.att.com/) from [Texas Instruments LaunchPad](http://www.ti.com/launchpad) development kits. It is compatible with any Energia enabled software environments and tested in the [Energia IDE](http://www.energia.nu).

**NOTE**: Unless stated otherwise, the following instructions are specific to [CC3200 SimpleLink Wi-Fi LaunchPad CC3200-LAUNCHXL](http://www.ti.com/tool/cc3200-launchxl), [TM4C129 Connected LaunchPad EK-TM4C1294XL](http://www.ti.com/tool/ek-tm4c1294xl), and any LaunchPads compatible with the [CC3100  BoosterPack](http://www.ti.com/tool/cc3100boost) including [MSP430F5529 LaunchPad](http://www.ti.com/tool/msp-exp430f5529lp), [MSP432 LaunchPad](http://www.ti.com/tool/msp-exp432p401r), and [TM4C123 LaunchPad EK-TM4C123GXL](http://www.ti.com/tool/ek-tm4c123gxl). If you are using other boards, the exact steps may vary.

The LaunchPad Energia library is based on the [attm2x/m2x-arduino](https://github.com/attm2x/m2x-arduino) library.

**NOTE**: We've [changed](https://github.com/attm2x/m2x-arduino/commit/ca3a5484b371f011a30a523465b9aa517d61db25) one API to avoid ambiguity, if you are using the older version of client library, you might need to fix your code.

Getting Started
==========================
1. Signup for an [M2X Account](https://m2x.att.com/signup).
2. Obtain your _Master_ from the Master Keys tab of your [Account Settings](https://m2x.att.com/account) screen.
3. Create your first [Device](https://m2x.att.com/devices) and copy its _Device ID_.
4. Review the [M2X API Documentation](https://m2x.att.com/developer/documentation/v2/overview).
5. Obtain a [TI LaunchPad](http://www.ti.com/launchpad), either with built in Ethernet/Wi-Fi or with a Wi-Fi BoosterPack, and [set it up](http://www.ti.com/lit/ug/spmu296/spmu296.pdf).  These docs were written for [CC3200 SimpleLink Wi-Fi LaunchPad CC3200-LAUNCHXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-cc3200-launchxl.html#tabs), [TM4C123 LaunchPad EK-TM4C123GXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-ek-tm4c123gxl.html#tabs) with [SimpleLink™ Wi-Fi CC3100 BoosterPack](http://www.ti.com/tool/cc3100boost), and [Tiva C Series EK-TM4C1294XL](http://www.ti.com/ww/en/launchpad/launchpads-connected-ek-tm4c1294xl.html#tabs) boards.

Please consult the [M2X glossary](https://m2x.att.com/developer/documentation/v1/glossary) if you have questions about any M2X specific terms.

Energia + AT&T M2X: Video Tutorial
==========================
[![Energia + AT&T M2X: Video Tutorial](http://img.youtube.com/vi/5FPMf2Bjmv8/0.jpg)](https://www.youtube.com/watch?v=5FPMf2Bjmv8&feature=youtu.be)

How to Install the library
==========================

This library is designed for use with the [Energia IDE](http://energia.nu).  Directions for installing and configuring the IDE can be found [here](http://energia.nu/guide).  

1. Open the Energia IDE, click `Energia->Preferences...`, look for `Sketchbook location` and keep it somewhere. Then locate at this path using your file browser of choice, open the `libraries` folder at this path(create one if it does not exist already). Copy `M2XStreamClient` folder to this location.
2. Now you can find M2X examples under `File->Examples->M2XStreamClient`
3. Enjoy coding!

Hardware Setup
==============

Board Setup
-----------

The Energia website has a very good [tutorial](http://energia.nu/guide) on setting up the LaunchPad board. It contains detailed instructions on how to install the Energia IDE, and sets up your board for initial testing. Feel free to proceed to the [LaunchPad site](http://www.ti.com/launchpad) to get a basic idea on LaunchPad.

Wifi/Ethernet Shield Setup
--------------------------

The [CC3200 SimpleLink Wi-Fi LaunchPad CC3200-LAUNCHXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-cc3200-launchxl.html#tabs) has built-in Wi-Fi and does not need any additional hardware.  The [TM4C129 Connected LaunchPad EK-TM4C1294XL](http://www.ti.com/tool/ek-tm4c1294gxl) already has Ethernet on-board, and does not require any additional hardwre. 

If you are using a [TM4C123 LaunchPad EK-TM4C123GXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-ek-tm4c123gxl.html#tabs) board,to send data to the AT&amp;T M2X Data Service, or receive data from the AT&amp;T M2X Data Service, your LaunchPad board needs a connection to the Internet. Hence a [CC3100 SimpleLink™ Wi-Fi BoosterPack](http://www.ti.com/tool/cc3100boost) is needed to give your board the power to connect to the Internet. To install the BoosterPack (referred to as shield/cape in other ecosystems), insert the BoosterPack either on top or on the bottom of your LaunchPad board  — you can use the pins on the BoosterPack the same way as the real pins on the LaunchPad boards.

Sensor Setup
------------

Different sensors can be hooked up to a LaunchPad board to provide different properties including temperatures, humidity, etc. These are available as BoosterPacks and as modules such as the [Grove system](http://www.seeedstudio.com/wiki/GROVE_System) from Seeedstudio. You can also use a breadboard and wires to connect different sensors and components to your LaunchPad. For detailed tutorials on connecting different sensors, please refer to the Energia [Getting Started Guide](http://www.energia.nu/guide). To see a list of BoosterPacks you can check out the [TI BoosterPack page](http://www.ti.com/boosterpack).


Variables used in Examples
==========================

In order to run the given examples, different variables need to be configured. We will walk through those variables in this section.

Network Configuration
---------------------

If you are using a Wi-Fi BosoterPack or LaunchPad, the following variables need configuration:

```
char ssid[] = "<ssid>";
char pass[] = "<WPA password>";
```

Just fill in the SSID and password of the Wi-Fi hotspot, you should be good to go.

For an Ethernet BoosterPack or LaunchPad, the following variables are needed:

```
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,17);
```

For an Ethernet device, the MAC address should be printed on a sticker on the hardware. In a case where there is no MAC address shown on the board, you can use any MAC address, as long as it is not conflicted with another network device within the same LAN.

The IP address here is only used when DHCP fails to give a valid IP address. It is recommended, though not required, to provide a unique IP address here.


M2X API Key
-----------

Once you [register](https://m2x.att.com/signup) for an AT&amp;T M2X account, an API key is automatically generated for you. This key is called a _Primary Master Key_ and can be found in the _Master Keys_ tab of your [Account Settings](https://m2x.att.com/account). This key cannot be edited nor deleted, but it can be regenerated. It will give you full access to all APIs.

However, you can also create a _Device API Key_ associated with a given Device, you can use the Device API key to access the streams belonging to that Data Source.

You can customize this variable in the following line in the examples:

```
char m2xKey[] = "<M2X access key>";
```

Device ID
-------

A device is associated with a data source, it is a set of data streams, such as streams of locations, temperatures, etc. The following line is needed to configure the device used:

```
char deviceId[] = "<device id>";
```

Stream Name
------------

A stream in a device is a set of timed series data of a specific type(i,e. humidity, temperature), you can use the M2XStreamClient library to send stream values to M2X server, or receive stream values from M2X server. Use the following line to configure the stream if needed:

```
char streamName[] = "<stream name>";
```

Using the M2XStreamClient library
=========================

The M2X LaunchPad library can be used with both Wi-Fi connection and Ethernet connection. For a Wi-Fi connection, use the following code:

```
WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);
```

For an Ethernet connection, use the following code:

```
EthernetClient client;
M2XStreamClient m2xClient(&client, m2xKey);
```


In the M2XStreamClient, following types of API functions are provided here:

* `updateStreamValue`: Send stream value to M2X server
* `postMultiple`: Send multiple stream values to M2X server
* `listStreamValues`: Receive stream value from M2X server
* `updateLocation`: Send location value of a device to M2X server
* `readLocation`: Receive location values of a device from M2X server
* `deleteValues`: Delete stream values on M2X server

Returned values
---------------

For all those functions, the HTTP status code will be returned if we can fulfill a HTTP request. For example, `200` will be returned upon success, `401` will be returned if we didn't provide a valid M2X API Key.

Otherwise, the following error codes will be used:

```
static const int E_NOCONNECTION = -1;
static const int E_DISCONNECTED = -2;
static const int E_NOTREACHABLE = -3;
static const int E_INVALID = -4;
static const int E_JSON_INVALID = -5;
```

Post stream value
-----------------

The following functions can be used to post value to a stream, which belongs to a device:

```
template <class T>
int updateStreamValue(const char* deviceId, const char* streamName, T value);
```

Here we use C++ templates to generate functions for different types of values, feel free to use values of `float`, `int`, `long` or even `const char*` types here.

Post multiple values
--------------------

M2X also supports posting multiple values to multiple streams in one call, use the following function for this:

```
template <class T>
int postMultiple(const char* deviceId, int streamNum,
                 const char* names[], const int counts[],
                 const char* ats[], T values[]);
```

Please refer to the comments in the source code on how to use this function, basically, you need to provide the list of streams you want to post to, and values for each stream.

List stream value
-----------------

The following API is used to list values of a specific stream:

```
int listStreamValues(const char* deviceId, const char* streamName,
                     const char* query,
                     aJsonObject **out);

```

Besides the device ID and stream name, a query string is supported. Please refer to the [API documentation](https://m2x.att.com/developer/documentation/v2/device#List-Data-Stream-Values) for valid query parameters, the query parameters must be formatted as [urlencoded form](http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4.1).

The response of the API is parsed using [aJson](https://github.com/interactive-matter/aJson).

Update Datasource Location
--------------------------

You can use the following function to update the location for a data source(device):

```
template <class T>
int updateLocation(const char* deviceId, const char* name,
                   T latitude, T longitude, T elevation);
```

Different from stream values, locations are attached to devices rather than streams.

The reasons we are providing templated function is due to floating point value precision: on most LaunchPad boards, `double` is the same as `float`, i.e., 32-bit (4-byte) single precision floating number. That means only 7 digits in the number is reliable. When we are using `double` here to represent latitude/longitude, it means only 5 digits after the floating point is accurate, which means we can represent as accurate to ~1.1132m distance using `double` here. If you want to represent cordinates that are more specific, you need to use strings here.

Read Datasource Location
------------------------

You can use the following function to retrieve reported locations of a particular device.

```
int readLocation(const char* deviceId, aJsonObject **out);
```

The response here is also parsed via aJson.

Delete Values
-------------

You can use the following function to delete values within a stream by providing a `from` and `end` date/time:

```
int deleteValues(const char* deviceId, const char* streamName, 
                 const char* from, const char* end);
```

The timestamps `from` and `end` need to be in an ISO 8601 format: yyyy-mm-ddTHH:MM:SS.SSSZ. Note the Z for Zulu time.

Examples
========

We provide a series of examples that will help you get an idea of how to use the `M2XStreamClient` library to perform all kinds of tasks.

Note that the examples may apply to certain types of boards. For example, the ones with `Wifi` in the name apply to LaunchPad boards with a `CC3100 BoosterPack`, while the ones with `Ethernet` apply to LaunchPad boards with built-in ethernet.

Note that the examples contain fictionary variables, and that they need to be configured as per the instructions above before running on your LaunchPad board. Each of the examples here also needs an accessible Wi-Fi or Ethernet connection hooked up to your device.  For Wi-Fi, it is important that you use a hotspot that is friendly for embedded devices. Hotspots that have a welcome screen required to login will not work. 

In the `LaunchPadWifiPost` and `LaunchPadEthernetPost`, a temperature sensor, a breadboard and 5 wires are also needed to get temperature data, you need to wire the board like [this](http://cl.ly/image/3M0P3T1A0G0l) before running the code.

After you have configured your variables and the board, plug the LaunchPad board into your computer via a Micro-USB cable, click `Verify` in the Energia IDE, then click `Upload`, and the code should be uploaded to the board. You can check all the outputs in the `Serial Monitor` of the Energia IDE.  Ensure the baud rate in the code matches the baud rate of the Serial Monitor to correctly receive data. 

LaunchPad3200WifiPost
-----------------

This example shows how to send tilt values from the built-in accelerometer (on the [CC3200 SimpleLink Wi-Fi LaunchPad CC3200-LAUNCHXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-cc3200-launchxl.html#tabs)) to M2X server. Before running this, you need to have a valid M2X Key, a device ID and a stream name. 

LaunchPadWifiPost
-----------------

This example shows how to post temperatures to M2X server. Before running this, you need to have a valid M2X Key, a device ID and a stream name. The LaunchPad board needs to be configured like [this](http://cl.ly/image/3M0P3T1A0G0l). In this example, we are using a [TM4C123 LaunchPad EK-TM4C123GXL](http://www.ti.com/ww/en/launchpad/launchpads-connected-ek-tm4c123gxl.html#tabs) with [SimpleLink™ Wi-Fi CC3100 BoosterPack](http://www.ti.com/tool/cc3100boost) board. If you are using other boards, keep in mind that we are reading from `A0` in the code, the wiring should be similar to this one shown in the illustration.

LaunchPadWifiPostMultiple
---------------

This example shows how to post multiple values to multiple streams in one API call.

LaunchPadWifiFetchValues
--------------

This example reads stream values from M2X server and prints the stream data points out to Serial interface. You can find the actual values in the Energia `Serial Monitor`.

LaunchPadWifiUpdateLocation
-----------------

This one sends location data to M2X server. Ideally, a GPS device should be used here to read the cordinates, but for simplicity, we just use pre-set values here to show how to use the API.

LaunchPadWifiReadLocation
---------------

This one reads location data of a device from M2X server, and prints them to Serial interface. You can check the output in the `Serial Monitor` of the Energia IDE.

LaunchPadWifiDelete
---------

This example shows how to delete values within a stream by providing a date/time range.

LaunchPadEthernetPost
---------------

This one is similar to the `LaunchPadWifiPost`, except that EthernetClient is used instead of WifiClient. If you are using a [TM4C129 Connected LaunchPad EK-TM4C1294XL](http://www.ti.com/ww/en/launchpad/launchpads-connected-ek-tm4c1294xl.html#tabs) board, you can use this example.

LaunchPadEthernetReceive
------------------

This one is similar to the `LaunchPadWifiReceive`, except that EthernetClient is used instead of WifiClient.



LICENSE
=======

This library is released under the MIT license. See [`M2XStreamClient/LICENSE`](M2XStreamClient/LICENSE) for the terms.
