<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="UCSA" />
        <signal name="UCSB" />
        <signal name="UCSC" />
        <signal name="UCSD" />
        <port polarity="Input" name="UCSA" />
        <port polarity="Input" name="UCSB" />
        <port polarity="Input" name="UCSC" />
        <port polarity="Input" name="UCSD" />
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
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin name="I0" />
            <blockpin name="I1" />
            <blockpin name="O" />
        </block>
        <block symbolname="or4" name="XLXI_3">
            <blockpin signalname="UCSD" name="I0" />
            <blockpin signalname="UCSC" name="I1" />
            <blockpin signalname="UCSB" name="I2" />
            <blockpin signalname="UCSA" name="I3" />
            <blockpin name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="656" y="688" name="XLXI_1" orien="R0" />
        <instance x="608" y="1840" name="XLXI_3" orien="R0" />
        <branch name="UCSA">
            <wire x2="608" y1="1584" y2="1584" x1="384" />
        </branch>
        <branch name="UCSB">
            <wire x2="608" y1="1648" y2="1648" x1="384" />
        </branch>
        <branch name="UCSC">
            <wire x2="592" y1="1712" y2="1712" x1="384" />
            <wire x2="608" y1="1712" y2="1712" x1="592" />
        </branch>
        <branch name="UCSD">
            <wire x2="608" y1="1776" y2="1776" x1="384" />
        </branch>
        <iomarker fontsize="28" x="384" y="1584" name="UCSA" orien="R180" />
        <iomarker fontsize="28" x="384" y="1648" name="UCSB" orien="R180" />
        <iomarker fontsize="28" x="384" y="1776" name="UCSD" orien="R180" />
        <iomarker fontsize="28" x="384" y="1712" name="UCSC" orien="R180" />
        <instance x="1168" y="1328" name="XLXI_2" orien="R0" />
    </sheet>
</drawing>