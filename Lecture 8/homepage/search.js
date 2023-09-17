function search()
{
    let input = document.querySelector('input');


    input.addEventListener("input", function(event) {

        let html = '';

        if (input.value)
        {
            for (tag of document.querySelectorAll('a'))
            {
                if (tag.innerHTML.toLowerCase().startsWith(input.value.toLowerCase()))
                {
                    if (html != tag.outerHTML && tag.innerHTML != html)
                    {

                        html += `${tag.outerHTML}`;

                    }


                }
            }
        }

        if (html != '' && html.length > 0)
        {
            var new_row = document.createElement('ul')
            var new_elem = document.querySelector('.d-flex').appendChild(new_row);
            new_elem.className = 'newElemClass';
            document.querySelector('.newElemClass').innerHTML = html;
        }



    });

}