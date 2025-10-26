<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="PORTAQ(15:0)" />
        <signal name="TRISAQ(15:0)" />
        <signal name="IOPORT(15)" />
        <signal name="IOPORT(0)" />
        <signal name="IOPORT(1)" />
        <signal name="IOPORT(2)" />
        <signal name="IOPORT(3)" />
        <signal name="IOPORT(4)" />
        <signal name="IOPORT(5)" />
        <signal name="IOPORT(6)" />
        <signal name="IOPORT(7)" />
        <signal name="IOPORT(8)" />
        <signal name="IOPORT(9)" />
        <signal name="IOPORT(10)" />
        <signal name="IOPORT(11)" />
        <signal name="IOPORT(12)" />
        <signal name="IOPORT(13)" />
        <signal name="IOPORT(14)" />
        <signal name="IOPORT(0:15)" />
        <signal name="TRISAQ(0)" />
        <signal name="PORTAQ(0)" />
        <signal name="TRISAQ(1)" />
        <signal name="PORTAQ(1)" />
        <signal name="TRISAQ(2)" />
        <signal name="PORTAQ(2)" />
        <signal name="TRISAQ(3)" />
        <signal name="PORTAQ(3)" />
        <signal name="TRISAQ(4)" />
        <signal name="PORTAQ(4)" />
        <signal name="TRISAQ(5)" />
        <signal name="PORTAQ(5)" />
        <signal name="TRISAQ(6)" />
        <signal name="PORTAQ(6)" />
        <signal name="TRISAQ(7)" />
        <signal name="PORTAQ(7)" />
        <signal name="TRISAQ(8)" />
        <signal name="PORTAQ(8)" />
        <signal name="TRISAQ(9)" />
        <signal name="PORTAQ(9)" />
        <signal name="TRISAQ(10)" />
        <signal name="PORTAQ(10)" />
        <signal name="TRISAQ(11)" />
        <signal name="PORTAQ(11)" />
        <signal name="TRISAQ(12)" />
        <signal name="PORTAQ(12)" />
        <signal name="TRISAQ(13)" />
        <signal name="PORTAQ(13)" />
        <signal name="TRISAQ(14)" />
        <signal name="PORTAQ(14)" />
        <signal name="TRISAQ(15)" />
        <signal name="PORTAQ(15)" />
        <signal name="XLXN_171" />
        <signal name="WR" />
        <signal name="PORTCS" />
        <signal name="XLXN_173" />
        <signal name="TRISCS" />
        <signal name="D(15:0)" />
        <signal name="IOIN(15:0)" />
        <port polarity="BiDirectional" name="IOPORT(0:15)" />
        <port polarity="Input" name="WR" />
        <port polarity="Input" name="PORTCS" />
        <port polarity="Input" name="TRISCS" />
        <port polarity="Input" name="D(15:0)" />
        <port polarity="Output" name="IOIN(15:0)" />
        <blockdef name="obufe">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-96" y2="-96" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-96" y2="-96" x1="96" />
            <line x2="96" y1="-48" y2="-96" x1="96" />
            <line x2="64" y1="-64" y2="0" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="128" y1="0" y2="-32" x1="64" />
        </blockdef>
        <blockdef name="ld16">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="64" x="0" y="-268" height="24" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="ibuf16">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="96" x="128" y="-44" height="24" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <rect width="64" x="0" y="-44" height="24" />
        </blockdef>
        <block symbolname="ld16" name="XLXI_41">
            <blockpin signalname="D(15:0)" name="D(15:0)" />
            <blockpin signalname="XLXN_171" name="G" />
            <blockpin signalname="PORTAQ(15:0)" name="Q(15:0)" />
        </block>
        <block symbolname="ld16" name="XLXI_40">
            <blockpin signalname="D(15:0)" name="D(15:0)" />
            <blockpin signalname="XLXN_173" name="G" />
            <blockpin signalname="TRISAQ(15:0)" name="Q(15:0)" />
        </block>
        <block symbolname="obufe" name="XLXI_194">
            <blockpin signalname="TRISAQ(15)" name="E" />
            <blockpin signalname="PORTAQ(15)" name="I" />
            <blockpin signalname="IOPORT(15)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_18">
            <blockpin signalname="TRISAQ(0)" name="E" />
            <blockpin signalname="PORTAQ(0)" name="I" />
            <blockpin signalname="IOPORT(0)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_17">
            <blockpin signalname="TRISAQ(1)" name="E" />
            <blockpin signalname="PORTAQ(1)" name="I" />
            <blockpin signalname="IOPORT(1)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_16">
            <blockpin signalname="TRISAQ(2)" name="E" />
            <blockpin signalname="PORTAQ(2)" name="I" />
            <blockpin signalname="IOPORT(2)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_15">
            <blockpin signalname="TRISAQ(3)" name="E" />
            <blockpin signalname="PORTAQ(3)" name="I" />
            <blockpin signalname="IOPORT(3)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_13">
            <blockpin signalname="TRISAQ(4)" name="E" />
            <blockpin signalname="PORTAQ(4)" name="I" />
            <blockpin signalname="IOPORT(4)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_12">
            <blockpin signalname="TRISAQ(5)" name="E" />
            <blockpin signalname="PORTAQ(5)" name="I" />
            <blockpin signalname="IOPORT(5)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_11">
            <blockpin signalname="TRISAQ(6)" name="E" />
            <blockpin signalname="PORTAQ(6)" name="I" />
            <blockpin signalname="IOPORT(6)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_10">
            <blockpin signalname="TRISAQ(7)" name="E" />
            <blockpin signalname="PORTAQ(7)" name="I" />
            <blockpin signalname="IOPORT(7)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_9">
            <blockpin signalname="TRISAQ(8)" name="E" />
            <blockpin signalname="PORTAQ(8)" name="I" />
            <blockpin signalname="IOPORT(8)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_8">
            <blockpin signalname="TRISAQ(9)" name="E" />
            <blockpin signalname="PORTAQ(9)" name="I" />
            <blockpin signalname="IOPORT(9)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_7">
            <blockpin signalname="TRISAQ(10)" name="E" />
            <blockpin signalname="PORTAQ(10)" name="I" />
            <blockpin signalname="IOPORT(10)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_6">
            <blockpin signalname="TRISAQ(11)" name="E" />
            <blockpin signalname="PORTAQ(11)" name="I" />
            <blockpin signalname="IOPORT(11)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_5">
            <blockpin signalname="TRISAQ(12)" name="E" />
            <blockpin signalname="PORTAQ(12)" name="I" />
            <blockpin signalname="IOPORT(12)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_4">
            <blockpin signalname="TRISAQ(13)" name="E" />
            <blockpin signalname="PORTAQ(13)" name="I" />
            <blockpin signalname="IOPORT(13)" name="O" />
        </block>
        <block symbolname="obufe" name="XLXI_3">
            <blockpin signalname="TRISAQ(14)" name="E" />
            <blockpin signalname="PORTAQ(14)" name="I" />
            <blockpin signalname="IOPORT(14)" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_239">
            <blockpin signalname="PORTCS" name="I0" />
            <blockpin signalname="WR" name="I1" />
            <blockpin signalname="XLXN_171" name="O" />
        </block>
        <block symbolname="ibuf16" name="XLXI_240">
            <blockpin signalname="IOPORT(0:15)" name="I(15:0)" />
            <blockpin signalname="IOIN(15:0)" name="O(15:0)" />
        </block>
        <block symbolname="and2" name="XLXI_241">
            <blockpin signalname="WR" name="I0" />
            <blockpin signalname="TRISCS" name="I1" />
            <blockpin signalname="XLXN_173" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <bustap x2="1936" y1="400" y2="400" x1="1840" />
        <bustap x2="1936" y1="256" y2="256" x1="1840" />
        <bustap x2="2000" y1="480" y2="480" x1="1904" />
        <bustap x2="2000" y1="336" y2="336" x1="1904" />
        <bustap x2="2000" y1="192" y2="192" x1="1904" />
        <instance x="1248" y="800" name="XLXI_41" orien="R0" />
        <instance x="1248" y="400" name="XLXI_40" orien="R0" />
        <branch name="PORTAQ(15:0)">
            <wire x2="1712" y1="544" y2="544" x1="1632" />
            <wire x2="1712" y1="176" y2="544" x1="1712" />
            <wire x2="1840" y1="176" y2="176" x1="1712" />
            <wire x2="1840" y1="176" y2="256" x1="1840" />
            <wire x2="1840" y1="256" y2="400" x1="1840" />
            <wire x2="1840" y1="400" y2="544" x1="1840" />
            <wire x2="1840" y1="544" y2="688" x1="1840" />
            <wire x2="1840" y1="688" y2="832" x1="1840" />
            <wire x2="1840" y1="832" y2="976" x1="1840" />
            <wire x2="1840" y1="976" y2="1120" x1="1840" />
            <wire x2="1840" y1="1120" y2="1264" x1="1840" />
            <wire x2="1840" y1="1264" y2="1408" x1="1840" />
            <wire x2="1840" y1="1408" y2="1552" x1="1840" />
            <wire x2="1840" y1="1552" y2="1696" x1="1840" />
            <wire x2="1840" y1="1696" y2="1840" x1="1840" />
            <wire x2="1840" y1="1840" y2="1984" x1="1840" />
            <wire x2="1840" y1="1984" y2="2128" x1="1840" />
            <wire x2="1840" y1="2128" y2="2272" x1="1840" />
            <wire x2="1840" y1="2272" y2="2416" x1="1840" />
            <wire x2="1840" y1="2416" y2="2432" x1="1840" />
        </branch>
        <branch name="TRISAQ(15:0)">
            <wire x2="1904" y1="144" y2="144" x1="1632" />
            <wire x2="1904" y1="144" y2="192" x1="1904" />
            <wire x2="1904" y1="192" y2="336" x1="1904" />
            <wire x2="1904" y1="336" y2="480" x1="1904" />
            <wire x2="1904" y1="480" y2="624" x1="1904" />
            <wire x2="1904" y1="624" y2="768" x1="1904" />
            <wire x2="1904" y1="768" y2="912" x1="1904" />
            <wire x2="1904" y1="912" y2="1056" x1="1904" />
            <wire x2="1904" y1="1056" y2="1200" x1="1904" />
            <wire x2="1904" y1="1200" y2="1344" x1="1904" />
            <wire x2="1904" y1="1344" y2="1488" x1="1904" />
            <wire x2="1904" y1="1488" y2="1632" x1="1904" />
            <wire x2="1904" y1="1632" y2="1776" x1="1904" />
            <wire x2="1904" y1="1776" y2="1920" x1="1904" />
            <wire x2="1904" y1="1920" y2="2064" x1="1904" />
            <wire x2="1904" y1="2064" y2="2208" x1="1904" />
            <wire x2="1904" y1="2208" y2="2352" x1="1904" />
            <wire x2="1904" y1="2352" y2="2368" x1="1904" />
        </branch>
        <bustap x2="2512" y1="2416" y2="2416" x1="2608" />
        <instance x="2192" y="2448" name="XLXI_194" orien="R0" />
        <instance x="2192" y="288" name="XLXI_18" orien="R0" />
        <instance x="2192" y="432" name="XLXI_17" orien="R0" />
        <instance x="2192" y="576" name="XLXI_16" orien="R0" />
        <instance x="2192" y="720" name="XLXI_15" orien="R0" />
        <instance x="2192" y="864" name="XLXI_13" orien="R0" />
        <instance x="2192" y="1008" name="XLXI_12" orien="R0" />
        <instance x="2192" y="1152" name="XLXI_11" orien="R0" />
        <instance x="2192" y="1296" name="XLXI_10" orien="R0" />
        <instance x="2192" y="1440" name="XLXI_9" orien="R0" />
        <instance x="2192" y="1584" name="XLXI_8" orien="R0" />
        <instance x="2192" y="1728" name="XLXI_7" orien="R0" />
        <instance x="2192" y="1872" name="XLXI_6" orien="R0" />
        <instance x="2192" y="2016" name="XLXI_5" orien="R0" />
        <instance x="2192" y="2160" name="XLXI_4" orien="R0" />
        <instance x="2192" y="2304" name="XLXI_3" orien="R0" />
        <bustap x2="2512" y1="256" y2="256" x1="2608" />
        <bustap x2="2512" y1="400" y2="400" x1="2608" />
        <bustap x2="2512" y1="544" y2="544" x1="2608" />
        <bustap x2="2512" y1="688" y2="688" x1="2608" />
        <bustap x2="2512" y1="832" y2="832" x1="2608" />
        <bustap x2="2512" y1="976" y2="976" x1="2608" />
        <bustap x2="2512" y1="1120" y2="1120" x1="2608" />
        <bustap x2="2512" y1="1264" y2="1264" x1="2608" />
        <bustap x2="2512" y1="1408" y2="1408" x1="2608" />
        <bustap x2="2512" y1="1552" y2="1552" x1="2608" />
        <bustap x2="2512" y1="1696" y2="1696" x1="2608" />
        <bustap x2="2512" y1="1840" y2="1840" x1="2608" />
        <bustap x2="2512" y1="1984" y2="1984" x1="2608" />
        <bustap x2="2512" y1="2128" y2="2128" x1="2608" />
        <bustap x2="2512" y1="2272" y2="2272" x1="2608" />
        <branch name="IOPORT(15)">
            <wire x2="2512" y1="2416" y2="2416" x1="2416" />
        </branch>
        <branch name="IOPORT(0)">
            <wire x2="2512" y1="256" y2="256" x1="2416" />
        </branch>
        <branch name="IOPORT(1)">
            <wire x2="2512" y1="400" y2="400" x1="2416" />
        </branch>
        <branch name="IOPORT(2)">
            <wire x2="2512" y1="544" y2="544" x1="2416" />
        </branch>
        <branch name="IOPORT(3)">
            <wire x2="2512" y1="688" y2="688" x1="2416" />
        </branch>
        <branch name="IOPORT(4)">
            <wire x2="2512" y1="832" y2="832" x1="2416" />
        </branch>
        <branch name="IOPORT(5)">
            <wire x2="2512" y1="976" y2="976" x1="2416" />
        </branch>
        <branch name="IOPORT(6)">
            <wire x2="2512" y1="1120" y2="1120" x1="2416" />
        </branch>
        <branch name="IOPORT(7)">
            <wire x2="2512" y1="1264" y2="1264" x1="2416" />
        </branch>
        <branch name="IOPORT(8)">
            <wire x2="2512" y1="1408" y2="1408" x1="2416" />
        </branch>
        <branch name="IOPORT(9)">
            <wire x2="2512" y1="1552" y2="1552" x1="2416" />
        </branch>
        <branch name="IOPORT(10)">
            <wire x2="2512" y1="1696" y2="1696" x1="2416" />
        </branch>
        <branch name="IOPORT(11)">
            <wire x2="2512" y1="1840" y2="1840" x1="2416" />
        </branch>
        <branch name="IOPORT(12)">
            <wire x2="2512" y1="1984" y2="1984" x1="2416" />
        </branch>
        <branch name="IOPORT(13)">
            <wire x2="2512" y1="2128" y2="2128" x1="2416" />
        </branch>
        <branch name="IOPORT(14)">
            <wire x2="2512" y1="2272" y2="2272" x1="2416" />
        </branch>
        <branch name="IOPORT(0:15)">
            <wire x2="2608" y1="2544" y2="2544" x1="2352" />
            <wire x2="2608" y1="96" y2="256" x1="2608" />
            <wire x2="2608" y1="256" y2="400" x1="2608" />
            <wire x2="2608" y1="400" y2="544" x1="2608" />
            <wire x2="2608" y1="544" y2="688" x1="2608" />
            <wire x2="2608" y1="688" y2="832" x1="2608" />
            <wire x2="2608" y1="832" y2="976" x1="2608" />
            <wire x2="2608" y1="976" y2="1120" x1="2608" />
            <wire x2="2608" y1="1120" y2="1264" x1="2608" />
            <wire x2="2608" y1="1264" y2="1408" x1="2608" />
            <wire x2="2608" y1="1408" y2="1552" x1="2608" />
            <wire x2="2608" y1="1552" y2="1696" x1="2608" />
            <wire x2="2608" y1="1696" y2="1840" x1="2608" />
            <wire x2="2608" y1="1840" y2="1984" x1="2608" />
            <wire x2="2608" y1="1984" y2="2128" x1="2608" />
            <wire x2="2608" y1="2128" y2="2272" x1="2608" />
            <wire x2="2608" y1="2272" y2="2416" x1="2608" />
            <wire x2="2608" y1="2416" y2="2544" x1="2608" />
            <wire x2="3136" y1="96" y2="96" x1="2608" />
        </branch>
        <iomarker fontsize="28" x="3136" y="96" name="IOPORT(0:15)" orien="R0" />
        <branch name="TRISAQ(0)">
            <wire x2="2192" y1="192" y2="192" x1="2000" />
        </branch>
        <branch name="PORTAQ(0)">
            <wire x2="2192" y1="256" y2="256" x1="1936" />
        </branch>
        <branch name="TRISAQ(1)">
            <wire x2="2192" y1="336" y2="336" x1="2000" />
        </branch>
        <branch name="PORTAQ(1)">
            <wire x2="2192" y1="400" y2="400" x1="1936" />
        </branch>
        <branch name="TRISAQ(2)">
            <wire x2="2192" y1="480" y2="480" x1="2000" />
        </branch>
        <bustap x2="2000" y1="624" y2="624" x1="1904" />
        <bustap x2="2000" y1="768" y2="768" x1="1904" />
        <bustap x2="2000" y1="912" y2="912" x1="1904" />
        <bustap x2="2000" y1="1056" y2="1056" x1="1904" />
        <bustap x2="2000" y1="1200" y2="1200" x1="1904" />
        <bustap x2="2000" y1="1344" y2="1344" x1="1904" />
        <bustap x2="2000" y1="1488" y2="1488" x1="1904" />
        <bustap x2="2000" y1="1632" y2="1632" x1="1904" />
        <bustap x2="2000" y1="1776" y2="1776" x1="1904" />
        <bustap x2="2000" y1="1920" y2="1920" x1="1904" />
        <bustap x2="2000" y1="2064" y2="2064" x1="1904" />
        <bustap x2="2000" y1="2208" y2="2208" x1="1904" />
        <bustap x2="2000" y1="2352" y2="2352" x1="1904" />
        <bustap x2="1936" y1="2416" y2="2416" x1="1840" />
        <bustap x2="1936" y1="2272" y2="2272" x1="1840" />
        <bustap x2="1936" y1="2128" y2="2128" x1="1840" />
        <bustap x2="1936" y1="1984" y2="1984" x1="1840" />
        <bustap x2="1936" y1="1840" y2="1840" x1="1840" />
        <bustap x2="1936" y1="1696" y2="1696" x1="1840" />
        <bustap x2="1936" y1="1552" y2="1552" x1="1840" />
        <bustap x2="1936" y1="1408" y2="1408" x1="1840" />
        <bustap x2="1936" y1="1264" y2="1264" x1="1840" />
        <bustap x2="1936" y1="1120" y2="1120" x1="1840" />
        <bustap x2="1936" y1="976" y2="976" x1="1840" />
        <bustap x2="1936" y1="832" y2="832" x1="1840" />
        <bustap x2="1936" y1="688" y2="688" x1="1840" />
        <bustap x2="1936" y1="544" y2="544" x1="1840" />
        <branch name="PORTAQ(2)">
            <wire x2="2192" y1="544" y2="544" x1="1936" />
        </branch>
        <branch name="TRISAQ(3)">
            <wire x2="2192" y1="624" y2="624" x1="2000" />
        </branch>
        <branch name="PORTAQ(3)">
            <wire x2="2192" y1="688" y2="688" x1="1936" />
        </branch>
        <branch name="TRISAQ(4)">
            <wire x2="2192" y1="768" y2="768" x1="2000" />
        </branch>
        <branch name="PORTAQ(4)">
            <wire x2="2192" y1="832" y2="832" x1="1936" />
        </branch>
        <branch name="TRISAQ(5)">
            <wire x2="2192" y1="912" y2="912" x1="2000" />
        </branch>
        <branch name="PORTAQ(5)">
            <wire x2="2192" y1="976" y2="976" x1="1936" />
        </branch>
        <branch name="TRISAQ(6)">
            <wire x2="2192" y1="1056" y2="1056" x1="2000" />
        </branch>
        <branch name="PORTAQ(6)">
            <wire x2="2192" y1="1120" y2="1120" x1="1936" />
        </branch>
        <branch name="TRISAQ(7)">
            <wire x2="2192" y1="1200" y2="1200" x1="2000" />
        </branch>
        <branch name="PORTAQ(7)">
            <wire x2="2192" y1="1264" y2="1264" x1="1936" />
        </branch>
        <branch name="TRISAQ(8)">
            <wire x2="2192" y1="1344" y2="1344" x1="2000" />
        </branch>
        <branch name="PORTAQ(8)">
            <wire x2="2192" y1="1408" y2="1408" x1="1936" />
        </branch>
        <branch name="TRISAQ(9)">
            <wire x2="2192" y1="1488" y2="1488" x1="2000" />
        </branch>
        <branch name="PORTAQ(9)">
            <wire x2="2192" y1="1552" y2="1552" x1="1936" />
        </branch>
        <branch name="TRISAQ(10)">
            <wire x2="2192" y1="1632" y2="1632" x1="2000" />
        </branch>
        <branch name="PORTAQ(10)">
            <wire x2="2192" y1="1696" y2="1696" x1="1936" />
        </branch>
        <branch name="TRISAQ(11)">
            <wire x2="2192" y1="1776" y2="1776" x1="2000" />
        </branch>
        <branch name="PORTAQ(11)">
            <wire x2="2192" y1="1840" y2="1840" x1="1936" />
        </branch>
        <branch name="TRISAQ(12)">
            <wire x2="2192" y1="1920" y2="1920" x1="2000" />
        </branch>
        <branch name="PORTAQ(12)">
            <wire x2="2192" y1="1984" y2="1984" x1="1936" />
        </branch>
        <branch name="TRISAQ(13)">
            <wire x2="2192" y1="2064" y2="2064" x1="2000" />
        </branch>
        <branch name="PORTAQ(13)">
            <wire x2="2192" y1="2128" y2="2128" x1="1936" />
        </branch>
        <branch name="TRISAQ(14)">
            <wire x2="2192" y1="2208" y2="2208" x1="2000" />
        </branch>
        <branch name="PORTAQ(14)">
            <wire x2="2192" y1="2272" y2="2272" x1="1936" />
        </branch>
        <branch name="TRISAQ(15)">
            <wire x2="2192" y1="2352" y2="2352" x1="2000" />
        </branch>
        <branch name="PORTAQ(15)">
            <wire x2="2192" y1="2416" y2="2416" x1="1936" />
        </branch>
        <instance x="928" y="768" name="XLXI_239" orien="R0" />
        <branch name="XLXN_171">
            <wire x2="1248" y1="672" y2="672" x1="1184" />
        </branch>
        <iomarker fontsize="28" x="768" y="704" name="PORTCS" orien="R180" />
        <branch name="WR">
            <wire x2="864" y1="640" y2="640" x1="768" />
            <wire x2="928" y1="640" y2="640" x1="864" />
            <wire x2="928" y1="320" y2="320" x1="864" />
            <wire x2="864" y1="320" y2="640" x1="864" />
        </branch>
        <iomarker fontsize="28" x="768" y="640" name="WR" orien="R180" />
        <iomarker fontsize="28" x="368" y="2544" name="IOIN(15:0)" orien="R180" />
        <instance x="2352" y="2512" name="XLXI_240" orien="R180" />
        <branch name="PORTCS">
            <wire x2="928" y1="704" y2="704" x1="768" />
        </branch>
        <instance x="928" y="384" name="XLXI_241" orien="R0" />
        <branch name="XLXN_173">
            <wire x2="1216" y1="288" y2="288" x1="1184" />
            <wire x2="1216" y1="272" y2="288" x1="1216" />
            <wire x2="1248" y1="272" y2="272" x1="1216" />
        </branch>
        <branch name="TRISCS">
            <wire x2="912" y1="256" y2="256" x1="752" />
            <wire x2="928" y1="256" y2="256" x1="912" />
        </branch>
        <iomarker fontsize="28" x="752" y="256" name="TRISCS" orien="R180" />
        <branch name="D(15:0)">
            <wire x2="576" y1="144" y2="144" x1="400" />
            <wire x2="1248" y1="144" y2="144" x1="576" />
            <wire x2="576" y1="144" y2="544" x1="576" />
            <wire x2="1248" y1="544" y2="544" x1="576" />
        </branch>
        <iomarker fontsize="28" x="400" y="144" name="D(15:0)" orien="R180" />
        <branch name="IOIN(15:0)">
            <wire x2="2128" y1="2544" y2="2544" x1="368" />
        </branch>
    </sheet>
</drawing>