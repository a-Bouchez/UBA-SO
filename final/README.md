# Final Sistemas Operativos - Schapa/Badder

Hice tantos finales de Schapa al pedo, me terminó tomando Badder aunque en el SIU salía el otro. Verifiquen por mail quien les toma.

Les recomiendo que lean los resueltos de este [link](https://docs.google.com/document/d/16gVrJF2UkiHtTxStT1kf1_tzc1j7VsuUTrITKYxm5ZA/edit?tab=t.0). Están muy bien explicados y cubren un montón de variantes que pueden caer.

---

Me tomaron el siguiente final escrito (no tengo ganas de escribir así que se lo mandé al 4to integrante misterioso, por las dudas chequeen las respuestas):

---

### 1. ¿Qué es una syscall?
- Es una llamada al sistema: una función que permite a un programa en espacio de usuario solicitar servicios al kernel (modo privilegiado).
- Involucra un cambio de contexto: pasa del modo usuario (ring 3) al modo kernel (ring 0).
- Tiene relación directa con los procesos porque es la forma en la que los procesos pueden interactuar con el SO (crear, leer archivos, etc).
  
**Cuatro syscalls importantes para archivos y qué hacen:**
- `open()`: abre un archivo y devuelve un file descriptor.
- `read()`: lee datos desde un archivo (usando el descriptor).
- `write()`: escribe datos en un archivo.
- `close()`: cierra un descriptor de archivo abierto.

---

### 2. ¿Qué es un deadlock? ¿Cómo evitarlo? (2 formas)

**Deadlock:** estado en el que dos o más procesos quedan bloqueados esperando recursos que nunca se liberarán.

**Dos formas de evitarlo:**
1. **Prevención:** garantizar que al menos una de las condiciones necesarias no ocurra (por ejemplo, evitar la espera circular usando orden total de los recursos).
2. **Evitación:** usar algoritmos como el **de Banquero** para asegurarse de que el sistema nunca entre en un estado inseguro.

---

### 3. Tres conceptos clave de LVM y cómo se relacionan

- **PV (Physical Volume):** un disco o partición real.
- **VG (Volume Group):** agrupación de uno o más PVs.
- **LV (Logical Volume):** partición lógica que se crea dentro de un VG, sobre la que montamos el sistema de archivos.

**Relación:** PVs → se agrupan en → VG → del que salen → LVs

**Dos ventajas de usar LVM:**
- Permite **redimensionar particiones fácilmente** (sin reiniciar ni formatear).
- Se pueden crear **snapshots** del sistema o de volúmenes individuales.

---

### 4. Contraseñas: ¿por qué se guardan en `/etc/shadow` y no en `/etc/passwd`?

- `/etc/passwd` es **legible por todos los usuarios**, contiene información básica como UID, GID, nombre, etc.
- Las contraseñas **no deben ir ahí**, por eso se guardan en `/etc/shadow`, que **sólo puede leer `root`**, mejorando la seguridad.

**Explicar hash y salt:**
- La contraseña no se guarda en texto plano, sino como **hash** (función unidireccional).
- Se le agrega un **salt** (valor aleatorio) antes de hashearla para evitar ataques por diccionario y rainbow tables.

**Si un atacante accede a `/etc/shadow`:**
- Puede hacer ataques de fuerza bruta offline.
  
**Mitigación:**
- Elegir contraseñas fuertes.
- Usar funciones hash lentas como bcrypt, scrypt o Argon2.
- Aplicar políticas de expiración y bloqueo por intentos.

---

### 5. Tres componentes clave del kernel de Linux para contenedores y qué hacen:

1. **Namespaces:** aíslan recursos del sistema (PID, red, usuarios, mount, etc.) por contenedor.
2. **Cgroups:** controlan el uso de recursos (CPU, RAM, I/O) de cada grupo de procesos.
3. **UnionFS / OverlayFS:** permiten montar un sistema de archivos sobre otro de forma que los cambios no afecten la base.

Con estos tres mecanismos el kernel permite ejecutar múltiples contenedores de manera aislada, segura y eficiente.

---
