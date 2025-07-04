/*
¿Cuál debería ser el nivel de acceso para las syscalls IN y OUT? ¿Por qué?

    Las syscalls IN y OUT se ejecutan en nivel kernel porque acceden de forma directa a los registros de los dispositivos de hardware. De esta forma
    un programa de usuario malicioso o mal implementado no puede acceder directamente a los dispositivos, necesita pasar por un driver, permitiendo así
    que el SO aplique los mecanismos de protección y seguridad. Por ejemplo, el programa de usuario necesita tener los permisos suficientes para hacerle
    open al driver.
*/