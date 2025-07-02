#!/bin/bash
echo -n "sistemas operativos por si o por no?"

read respuesta

if [ $respuesta = "si" ]
then
    echo -n "picado"
else
    echo -n  "aguante furfy"
fi 