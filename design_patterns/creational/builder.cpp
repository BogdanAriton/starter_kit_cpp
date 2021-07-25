/*

A builder is used to constrcut an object in steps.
For example if you have an html element you should be able to construct it and it's children in one go

Key elements is that the object for which we create the builder for will have a static function that will create an Builder instance
and the builder should be convertable to the object using an operator overload

class TheObject
{
    // this returns the builder that in turn returns an TheObject
    static TheBuilderObject build()
    {
        return TheObject();
    }
}

class TheBuilderObject
{
    TheObject myObject;
    operator TheObject ()
    {
        return myObject;
    }
}

 */